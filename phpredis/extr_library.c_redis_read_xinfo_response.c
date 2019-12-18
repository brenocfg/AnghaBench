#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int /*<<< orphan*/  zval ;
typedef  int /*<<< orphan*/  RedisSock ;
typedef  int REDIS_REPLY_TYPE ;

/* Variables and functions */
 int FAILURE ; 
 int SUCCESS ; 
#define  TYPE_BULK 130 
#define  TYPE_INT 129 
#define  TYPE_MULTIBULK 128 
 int /*<<< orphan*/  add_assoc_long_ex (int /*<<< orphan*/ *,char*,int,long) ; 
 int /*<<< orphan*/  add_assoc_stringl_ex (int /*<<< orphan*/ *,char*,int,char*,long) ; 
 int /*<<< orphan*/  add_assoc_zval_ex (int /*<<< orphan*/ *,char*,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  add_next_index_zval (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  array_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  efree (char*) ; 
 scalar_t__ redis_read_reply_type (int /*<<< orphan*/ *,int*,long*) ; 
 char* redis_sock_read_bulk_reply (int /*<<< orphan*/ *,long) ; 
 int spprintf (char**,int /*<<< orphan*/ ,char*,long) ; 
 int /*<<< orphan*/  zval_dtor (int /*<<< orphan*/ *) ; 

int
redis_read_xinfo_response(RedisSock *redis_sock, zval *z_ret, int elements)
{
    zval zv;
    int i, len;
    char *key = NULL, *data;
    REDIS_REPLY_TYPE type;
    long li;

    for (i = 0; i < elements; ++i) {
        if (redis_read_reply_type(redis_sock, &type, &li) < 0) {
            goto failure;
        }
        switch (type) {
        case TYPE_BULK:
            if ((data = redis_sock_read_bulk_reply(redis_sock, li)) == NULL) {
                goto failure;
            } else if (key) {
                add_assoc_stringl_ex(z_ret, key, len, data, li);
                efree(data);
                efree(key);
                key = NULL;
            } else {
                key = data;
                len = li;
            }
            break;
        case TYPE_INT:
            if (key) {
                add_assoc_long_ex(z_ret, key, len, li);
                efree(key);
                key = NULL;
            } else {
                len = spprintf(&key, 0, "%ld", li);
            }
            break;
        case TYPE_MULTIBULK:
            array_init(&zv);
            if (redis_read_xinfo_response(redis_sock, &zv, li) != SUCCESS) {
                zval_dtor(&zv);
                goto failure;
            }
            if (key) {
                add_assoc_zval_ex(z_ret, key, len, &zv);
                efree(key);
                key = NULL;
            } else {
                add_next_index_zval(z_ret, &zv);
            }
            break;
        default:
            goto failure;
        }
    }

    return SUCCESS;

failure:
    if (key) efree(key);
    return FAILURE;
}