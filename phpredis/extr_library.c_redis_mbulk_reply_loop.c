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
 int UNSERIALIZE_ALL ; 
 int UNSERIALIZE_KEYS ; 
 int UNSERIALIZE_VALS ; 
 int /*<<< orphan*/  add_next_index_bool (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  add_next_index_stringl (int /*<<< orphan*/ *,char*,int) ; 
 int /*<<< orphan*/  add_next_index_zval (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  efree (char*) ; 
 char* redis_sock_read (int /*<<< orphan*/ *,int*) ; 
 scalar_t__ redis_unpack (int /*<<< orphan*/ *,char*,int,int /*<<< orphan*/ *) ; 

void
redis_mbulk_reply_loop(RedisSock *redis_sock, zval *z_tab, int count,
                       int unserialize)
{
    zval z_unpacked;
    char *line;
    int i, len;

    for (i = 0; i < count; ++i) {
        if ((line = redis_sock_read(redis_sock, &len)) == NULL) {
            add_next_index_bool(z_tab, 0);
            continue;
        }

        /* We will attempt unserialization, if we're unserializing everything,
         * or if we're unserializing keys and we're on a key, or we're
         * unserializing values and we're on a value! */
        int unwrap = (
            (unserialize == UNSERIALIZE_ALL) ||
            (unserialize == UNSERIALIZE_KEYS && i % 2 == 0) ||
            (unserialize == UNSERIALIZE_VALS && i % 2 != 0)
        );

        if (unwrap && redis_unpack(redis_sock, line, len, &z_unpacked)) {
            add_next_index_zval(z_tab, &z_unpacked);
        } else {
            add_next_index_stringl(z_tab, line, len);
        }
        efree(line);
    }
}