#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int /*<<< orphan*/ * prefix; } ;
typedef  TYPE_1__ RedisSock ;

/* Variables and functions */
 int ZSTR_LEN (int /*<<< orphan*/ *) ; 
 char* ZSTR_VAL (int /*<<< orphan*/ *) ; 
 char* ecalloc (int,int) ; 
 int /*<<< orphan*/  memcpy (char*,char*,size_t) ; 

int
redis_key_prefix(RedisSock *redis_sock, char **key, size_t *key_len) {
    int ret_len;
    char *ret;

    if (redis_sock->prefix == NULL) {
        return 0;
    }

    ret_len = ZSTR_LEN(redis_sock->prefix) + *key_len;
    ret = ecalloc(1 + ret_len, 1);
    memcpy(ret, ZSTR_VAL(redis_sock->prefix), ZSTR_LEN(redis_sock->prefix));
    memcpy(ret + ZSTR_LEN(redis_sock->prefix), *key, *key_len);

    *key = ret;
    *key_len = ret_len;
    return 1;
}