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
 int FAILURE ; 
 int SUCCESS ; 
 int /*<<< orphan*/  add_next_index_stringl (int /*<<< orphan*/ *,char*,int) ; 
 int /*<<< orphan*/  efree (char*) ; 
 char* redis_sock_read (int /*<<< orphan*/ *,int*) ; 

int mbulk_resp_loop_raw(RedisSock *redis_sock, zval *z_result,
                        long long count, void *ctx)
{
    char *line;
    int line_len;

    // Iterate over the number we have
    while (count--) {
        // Read the line, which should never come back null
        line = redis_sock_read(redis_sock, &line_len);
        if (line == NULL) return FAILURE;

        // Add to our result array
        add_next_index_stringl(z_result, line, line_len);
        efree(line);
    }

    // Success!
    return SUCCESS;
}