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
 int SUCCESS ; 
 int /*<<< orphan*/  add_next_index_bool (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  add_next_index_stringl (int /*<<< orphan*/ *,char*,int) ; 
 int /*<<< orphan*/  add_next_index_zval (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  efree (char*) ; 
 char* redis_sock_read (int /*<<< orphan*/ *,int*) ; 
 scalar_t__ redis_unpack (int /*<<< orphan*/ *,char*,int,int /*<<< orphan*/ *) ; 

int mbulk_resp_loop(RedisSock *redis_sock, zval *z_result,
                    long long count, void *ctx)
{
    char *line;
    int line_len;

    /* Iterate over the lines we have to process */
    while (count--) {
        /* Read our line */
        line = redis_sock_read(redis_sock, &line_len);

        if (line != NULL) {
            zval z_unpacked;
            if (redis_unpack(redis_sock, line, line_len, &z_unpacked)) {
                add_next_index_zval(z_result, &z_unpacked);
            } else {
                add_next_index_stringl(z_result, line, line_len);
            }
            efree(line);
        } else {
            if (line) efree(line);
            add_next_index_bool(z_result, 0);
        }
    }

    return SUCCESS;
}