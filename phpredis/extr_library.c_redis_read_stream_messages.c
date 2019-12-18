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

/* Variables and functions */
 int /*<<< orphan*/  SCORE_DECODE_NONE ; 
 int /*<<< orphan*/  UNSERIALIZE_VALS ; 
 int /*<<< orphan*/  add_assoc_zval_ex (int /*<<< orphan*/ *,char*,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  array_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  array_zip_values_and_scores (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  efree (char*) ; 
 scalar_t__ read_mbulk_header (int /*<<< orphan*/ *,int*) ; 
 int /*<<< orphan*/  redis_mbulk_reply_loop (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 
 char* redis_sock_read (int /*<<< orphan*/ *,int*) ; 

int
redis_read_stream_messages(RedisSock *redis_sock, int count, zval *z_ret
                          )
{
    zval z_message;
    int i, mhdr, fields;
    char *id = NULL;
    int idlen;

    /* Iterate over each message */
    for (i = 0; i < count; i++) {
        /* Consume inner multi-bulk header, message ID itself and finaly
         * the multi-bulk header for field and values */
        if ((read_mbulk_header(redis_sock, &mhdr) < 0 || mhdr != 2) ||
            ((id = redis_sock_read(redis_sock, &idlen)) == NULL) ||
            (read_mbulk_header(redis_sock, &fields) < 0 || fields % 2 != 0))
        {
            if (id) efree(id);
            return -1;
        }

        array_init(&z_message);

        redis_mbulk_reply_loop(redis_sock, &z_message, fields, UNSERIALIZE_VALS);
        array_zip_values_and_scores(redis_sock, &z_message, SCORE_DECODE_NONE);
        add_assoc_zval_ex(z_ret, id, idlen, &z_message);
        efree(id);
    }

    return 0;
}