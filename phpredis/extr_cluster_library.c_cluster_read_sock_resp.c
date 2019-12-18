#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int type; size_t integer; size_t len; size_t elements; void* element; int /*<<< orphan*/  str; } ;
typedef  TYPE_1__ clusterReply ;
typedef  int /*<<< orphan*/  RedisSock ;
typedef  int REDIS_REPLY_TYPE ;

/* Variables and functions */
#define  TYPE_BULK 132 
#define  TYPE_ERR 131 
#define  TYPE_INT 130 
#define  TYPE_LINE 129 
#define  TYPE_MULTIBULK 128 
 int /*<<< orphan*/  cluster_free_reply (TYPE_1__*,int) ; 
 int /*<<< orphan*/  cluster_multibulk_resp_recursive (int /*<<< orphan*/ *,size_t,void*,int /*<<< orphan*/ ,int*) ; 
 void* ecalloc (size_t,int) ; 
 int /*<<< orphan*/  estrndup (char*,size_t) ; 
 int /*<<< orphan*/  redis_sock_read_bulk_reply (int /*<<< orphan*/ *,size_t) ; 

clusterReply*
cluster_read_sock_resp(RedisSock *redis_sock, REDIS_REPLY_TYPE type,
                       char *line_reply, size_t len)
{
    clusterReply *r;

    r = ecalloc(1, sizeof(clusterReply));
    r->type = type;

    // Error flag in case we go recursive
    int err = 0;

    switch(r->type) {
        case TYPE_INT:
            r->integer = len;
            break;
        case TYPE_LINE:
            if (line_reply) {
                r->str = estrndup(line_reply, len);
                r->len = len;
            }
        case TYPE_ERR:
            return r;
        case TYPE_BULK:
            r->len = len;
            r->str = redis_sock_read_bulk_reply(redis_sock, len);
            if (r->len != -1 && !r->str) {
                cluster_free_reply(r, 1);
                return NULL;
            }
            break;
        case TYPE_MULTIBULK:
            r->elements = len;
            if (len != (size_t)-1) {
                r->element = ecalloc(len, sizeof(clusterReply*));
                cluster_multibulk_resp_recursive(redis_sock, len, r->element,
                                                 line_reply != NULL, &err);
            }
            break;
        default:
            cluster_free_reply(r,1);
            return NULL;
    }

    // Free/return null on communication error
    if (err) {
        cluster_free_reply(r,1);
        return NULL;
    }

    // Success, return the reply
    return r;
}