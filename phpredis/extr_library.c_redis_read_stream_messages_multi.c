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
 int /*<<< orphan*/  add_assoc_zval_ex (int /*<<< orphan*/ *,char*,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  array_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  efree (char*) ; 
 scalar_t__ read_mbulk_header (int /*<<< orphan*/ *,int*) ; 
 scalar_t__ redis_read_stream_messages (int /*<<< orphan*/ *,int,int /*<<< orphan*/ *) ; 
 char* redis_sock_read (int /*<<< orphan*/ *,int*) ; 
 int /*<<< orphan*/  zval_dtor (int /*<<< orphan*/ *) ; 

int
redis_read_stream_messages_multi(RedisSock *redis_sock, int count, zval *z_streams
                                )
{
    zval z_messages;
    int i, shdr, messages;
    char *id = NULL;
    int idlen;

    for (i = 0; i < count; i++) {
        if ((read_mbulk_header(redis_sock, &shdr) < 0 || shdr != 2) ||
            (id = redis_sock_read(redis_sock, &idlen)) == NULL ||
            read_mbulk_header(redis_sock, &messages) < 0)
        {
            if (id) efree(id);
            return -1;
        }

        array_init(&z_messages);

        if (redis_read_stream_messages(redis_sock, messages, &z_messages) < 0)
            goto failure;

        add_assoc_zval_ex(z_streams, id, idlen, &z_messages);
        efree(id);
    }

    return 0;
failure:
    efree(id);
    zval_dtor(&z_messages);
    return -1;
}