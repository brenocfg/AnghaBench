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
typedef  int /*<<< orphan*/  inbuf ;
typedef  int /*<<< orphan*/  RedisSock ;

/* Variables and functions */
 int atoi (char*) ; 
 char* estrndup (char*,int) ; 
 int /*<<< orphan*/  memcmp (char*,char*,int) ; 
 int /*<<< orphan*/  redis_error_throw (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  redis_exception_ce ; 
 scalar_t__ redis_sock_gets (int /*<<< orphan*/ *,char*,int,size_t*) ; 
 char* redis_sock_read_bulk_reply (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  redis_sock_set_err (int /*<<< orphan*/ *,char*,size_t) ; 
 int /*<<< orphan*/  zend_throw_exception_ex (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,char) ; 

char *
redis_sock_read(RedisSock *redis_sock, int *buf_len)
{
    char inbuf[4096];
    size_t len;

    *buf_len = 0;
    if (redis_sock_gets(redis_sock, inbuf, sizeof(inbuf) - 1, &len) < 0) {
        return NULL;
    }

    switch(inbuf[0]) {
        case '-':
            redis_sock_set_err(redis_sock, inbuf+1, len);

            /* Filter our ERROR through the few that should actually throw */
            redis_error_throw(redis_sock);

            return NULL;
        case '$':
            *buf_len = atoi(inbuf + 1);
            return redis_sock_read_bulk_reply(redis_sock, *buf_len);

        case '*':
            /* For null multi-bulk replies (like timeouts from brpoplpush): */
            if(memcmp(inbuf + 1, "-1", 2) == 0) {
                return NULL;
            }
            /* fall through */

        case '+':
        case ':':
            /* Single Line Reply */
            /* +OK or :123 */
            if (len > 1) {
                *buf_len = len;
                return estrndup(inbuf, *buf_len);
            }
        default:
            zend_throw_exception_ex(redis_exception_ce, 0,
                "protocol error, got '%c' as reply type byte\n",
                inbuf[0]
            );
    }

    return NULL;
}