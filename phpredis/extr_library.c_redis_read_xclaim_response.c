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
typedef  scalar_t__ REDIS_REPLY_TYPE ;

/* Variables and functions */
 int /*<<< orphan*/  SCORE_DECODE_NONE ; 
 scalar_t__ TYPE_BULK ; 
 scalar_t__ TYPE_MULTIBULK ; 
 int /*<<< orphan*/  UNSERIALIZE_VALS ; 
 int /*<<< orphan*/  add_assoc_zval_ex (int /*<<< orphan*/ *,char*,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  add_next_index_stringl (int /*<<< orphan*/ *,char*,long) ; 
 int /*<<< orphan*/  array_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  array_zip_values_and_scores (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  efree (char*) ; 
 scalar_t__ read_mbulk_header (int /*<<< orphan*/ *,int*) ; 
 int /*<<< orphan*/  redis_mbulk_reply_loop (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 
 scalar_t__ redis_read_reply_type (int /*<<< orphan*/ *,scalar_t__*,long*) ; 
 char* redis_sock_read (int /*<<< orphan*/ *,int*) ; 
 char* redis_sock_read_bulk_reply (int /*<<< orphan*/ *,size_t) ; 

int
redis_read_xclaim_response(RedisSock *redis_sock, int count, zval *rv) {
    zval z_msg;
    REDIS_REPLY_TYPE type;
    char *id = NULL;
    int i, fields, idlen;
    long li;

    for (i = 0; i < count; i++) {
        /* Consume inner reply type */
        if (redis_read_reply_type(redis_sock, &type, &li) < 0 ||
            (type != TYPE_BULK && type != TYPE_MULTIBULK) ||
            (type == TYPE_BULK && li <= 0)) return -1;

        /* TYPE_BULK is the JUSTID variant, otherwise it's standard xclaim response */
        if (type == TYPE_BULK) {
            if ((id = redis_sock_read_bulk_reply(redis_sock, (size_t)li)) == NULL)
                return -1;

            add_next_index_stringl(rv, id, li);
            efree(id);
        } else {
            if ((li != 2 || (id = redis_sock_read(redis_sock, &idlen)) == NULL) ||
                (read_mbulk_header(redis_sock, &fields) < 0 || fields % 2 != 0))
            {
                if (id) efree(id);
                return -1;
            }

            array_init(&z_msg);

            redis_mbulk_reply_loop(redis_sock, &z_msg, fields, UNSERIALIZE_VALS);
            array_zip_values_and_scores(redis_sock, &z_msg, SCORE_DECODE_NONE);
            add_assoc_zval_ex(rv, id, idlen, &z_msg);
            efree(id);
        }
    }

    return 0;
}