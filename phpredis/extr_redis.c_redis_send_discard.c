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
typedef  int /*<<< orphan*/  RedisSock ;

/* Variables and functions */
 int FAILURE ; 
 int REDIS_SPPRINTF (char**,char*,char*) ; 
 int SUCCESS ; 
 int /*<<< orphan*/  efree (char*) ; 
 char* redis_sock_read (int /*<<< orphan*/ *,int*) ; 
 scalar_t__ redis_sock_write (int /*<<< orphan*/ *,char*,int) ; 
 scalar_t__ strncmp (char*,char*,int) ; 

__attribute__((used)) static int
redis_send_discard(RedisSock *redis_sock)
{
    int result = FAILURE;
    char *cmd, *resp;
    int resp_len, cmd_len;

    /* format our discard command */
    cmd_len = REDIS_SPPRINTF(&cmd, "DISCARD", "");

    /* send our DISCARD command */
    if (redis_sock_write(redis_sock, cmd, cmd_len) >= 0 &&
       (resp = redis_sock_read(redis_sock,&resp_len)) != NULL)
    {
        /* success if we get OK */
        result = (resp_len == 3 && strncmp(resp,"+OK", 3) == 0) ? SUCCESS:FAILURE;

        /* free our response */
        efree(resp);
    }

    /* free our command */
    efree(cmd);

    /* return success/failure */
    return result;
}