#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int /*<<< orphan*/  auth; } ;
typedef  TYPE_1__ RedisSock ;

/* Variables and functions */
 int /*<<< orphan*/  ZSTR_LEN (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ZSTR_VAL (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  efree (char*) ; 
 char* redis_sock_read (TYPE_1__*,int*) ; 
 scalar_t__ redis_sock_write (TYPE_1__*,char*,int) ; 
 int redis_spprintf (TYPE_1__*,int /*<<< orphan*/ *,char**,char*,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ strncmp (char*,char*,int) ; 

int
redis_sock_auth(RedisSock *redis_sock)
{
    char *cmd, *response;
    int cmd_len, response_len;

    cmd_len = redis_spprintf(redis_sock, NULL, &cmd, "AUTH", "s",
                             ZSTR_VAL(redis_sock->auth), ZSTR_LEN(redis_sock->auth));

    if (redis_sock_write(redis_sock, cmd, cmd_len) < 0) {
        efree(cmd);
        return -1;
    }

    efree(cmd);

    response = redis_sock_read(redis_sock, &response_len);
    if (response == NULL) {
        return -1;
    }

    if (strncmp(response, "+OK", 3)) {
        efree(response);
        return -1;
    }

    efree(response);
    return 0;
}