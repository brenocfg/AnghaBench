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
typedef  int /*<<< orphan*/  line ;
typedef  int /*<<< orphan*/  RedisSock ;

/* Variables and functions */
 scalar_t__ IS_ATOMIC (int /*<<< orphan*/ *) ; 
 int atoi (char*) ; 
 scalar_t__ redis_sock_gets (int /*<<< orphan*/ *,char*,int,size_t*) ; 
 int /*<<< orphan*/  redis_sock_set_err (int /*<<< orphan*/ *,char*,size_t) ; 

__attribute__((used)) static int
read_mbulk_header(RedisSock *redis_sock, int *nelem)
{
    char line[4096];
    size_t len;

    /* Throws exception on failure */
    if (redis_sock_gets(redis_sock, line, sizeof(line)-1, &len) < 0)
        return -1;

    if (line[0] != '*') {
        if (IS_ATOMIC(redis_sock)) {
            if (line[0] == '-') {
                redis_sock_set_err(redis_sock, line+1, len-1);
            }
        }
        return -1;
    }

    *nelem = atoi(line+1);

    return 0;
}