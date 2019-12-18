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
typedef  int /*<<< orphan*/  inbuf ;
typedef  int /*<<< orphan*/  RedisSock ;
typedef  scalar_t__ REDIS_REPLY_TYPE ;

/* Variables and functions */
 scalar_t__ TYPE_ERR ; 
 int /*<<< orphan*/  ZVAL_FALSE (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ZVAL_STRINGL (int /*<<< orphan*/ *,char*,size_t) ; 
 int /*<<< orphan*/  ZVAL_TRUE (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  redis_error_throw (int /*<<< orphan*/ *) ; 
 scalar_t__ redis_sock_gets (int /*<<< orphan*/ *,char*,int,size_t*) ; 
 int /*<<< orphan*/  redis_sock_set_err (int /*<<< orphan*/ *,char*,size_t) ; 

__attribute__((used)) static int
redis_read_variant_line(RedisSock *redis_sock, REDIS_REPLY_TYPE reply_type,
                        int as_string, zval *z_ret)
{
    // Buffer to read our single line reply
    char inbuf[4096];
    size_t len;

    /* Attempt to read our single line reply */
    if(redis_sock_gets(redis_sock, inbuf, sizeof(inbuf), &len) < 0) {
        return -1;
    }

    /* Throw exception on SYNC error otherwise just set error string */
    if(reply_type == TYPE_ERR) {
        redis_sock_set_err(redis_sock, inbuf, len);
        redis_error_throw(redis_sock);
        ZVAL_FALSE(z_ret);
    } else if (as_string) {
        ZVAL_STRINGL(z_ret, inbuf, len);
    } else {
        ZVAL_TRUE(z_ret);
    }

    return 0;
}