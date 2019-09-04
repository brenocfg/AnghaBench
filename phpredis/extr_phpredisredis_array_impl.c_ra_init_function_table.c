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
struct TYPE_3__ {int /*<<< orphan*/  pure_cmds; } ;
typedef  TYPE_1__ RedisArray ;

/* Variables and functions */
 int /*<<< orphan*/  ALLOC_HASHTABLE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  zend_hash_init (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  zend_hash_str_update_ptr (int /*<<< orphan*/ ,char*,int,int /*<<< orphan*/ *) ; 

void
ra_init_function_table(RedisArray *ra)
{
    ALLOC_HASHTABLE(ra->pure_cmds);
    zend_hash_init(ra->pure_cmds, 0, NULL, NULL, 0);

    zend_hash_str_update_ptr(ra->pure_cmds, "EXISTS", sizeof("EXISTS") - 1, NULL);
    zend_hash_str_update_ptr(ra->pure_cmds, "GET", sizeof("GET") - 1, NULL);
    zend_hash_str_update_ptr(ra->pure_cmds, "GETBIT", sizeof("GETBIT") - 1, NULL);
    zend_hash_str_update_ptr(ra->pure_cmds, "GETRANGE", sizeof("GETRANGE") - 1, NULL);
    zend_hash_str_update_ptr(ra->pure_cmds, "HEXISTS", sizeof("HEXISTS") - 1, NULL);
    zend_hash_str_update_ptr(ra->pure_cmds, "HGET", sizeof("HGET") - 1, NULL);
    zend_hash_str_update_ptr(ra->pure_cmds, "HGETALL", sizeof("HGETALL") - 1, NULL);
    zend_hash_str_update_ptr(ra->pure_cmds, "HKEYS", sizeof("HKEYS") - 1, NULL);
    zend_hash_str_update_ptr(ra->pure_cmds, "HLEN", sizeof("HLEN") - 1, NULL);
    zend_hash_str_update_ptr(ra->pure_cmds, "HMGET", sizeof("HMGET") - 1, NULL);
    zend_hash_str_update_ptr(ra->pure_cmds, "HVALS", sizeof("HVALS") - 1, NULL);
    zend_hash_str_update_ptr(ra->pure_cmds, "LINDEX", sizeof("LINDEX") - 1, NULL);
    zend_hash_str_update_ptr(ra->pure_cmds, "LLEN", sizeof("LLEN") - 1, NULL);
    zend_hash_str_update_ptr(ra->pure_cmds, "LRANGE", sizeof("LRANGE") - 1, NULL);
    zend_hash_str_update_ptr(ra->pure_cmds, "OBJECT", sizeof("OBJECT") - 1, NULL);
    zend_hash_str_update_ptr(ra->pure_cmds, "SCARD", sizeof("SCARD") - 1, NULL);
    zend_hash_str_update_ptr(ra->pure_cmds, "SDIFF", sizeof("SDIFF") - 1, NULL);
    zend_hash_str_update_ptr(ra->pure_cmds, "SINTER", sizeof("SINTER") - 1, NULL);
    zend_hash_str_update_ptr(ra->pure_cmds, "SISMEMBER", sizeof("SISMEMBER") - 1, NULL);
    zend_hash_str_update_ptr(ra->pure_cmds, "SMEMBERS", sizeof("SMEMBERS") - 1, NULL);
    zend_hash_str_update_ptr(ra->pure_cmds, "SRANDMEMBER", sizeof("SRANDMEMBER") - 1, NULL);
    zend_hash_str_update_ptr(ra->pure_cmds, "STRLEN", sizeof("STRLEN") - 1, NULL);
    zend_hash_str_update_ptr(ra->pure_cmds, "SUNION", sizeof("SUNION") - 1, NULL);
    zend_hash_str_update_ptr(ra->pure_cmds, "TYPE", sizeof("TYPE") - 1, NULL);
    zend_hash_str_update_ptr(ra->pure_cmds, "ZCARD", sizeof("ZCARD") - 1, NULL);
    zend_hash_str_update_ptr(ra->pure_cmds, "ZCOUNT", sizeof("ZCOUNT") - 1, NULL);
    zend_hash_str_update_ptr(ra->pure_cmds, "ZRANGE", sizeof("ZRANGE") - 1, NULL);
    zend_hash_str_update_ptr(ra->pure_cmds, "ZRANK", sizeof("ZRANK") - 1, NULL);
    zend_hash_str_update_ptr(ra->pure_cmds, "ZREVRANGE", sizeof("ZREVRANGE") - 1, NULL);
    zend_hash_str_update_ptr(ra->pure_cmds, "ZREVRANGEBYSCORE", sizeof("ZREVRANGEBYSCORE") - 1, NULL);
    zend_hash_str_update_ptr(ra->pure_cmds, "ZREVRANK", sizeof("ZREVRANK") - 1, NULL);
    zend_hash_str_update_ptr(ra->pure_cmds, "ZSCORE", sizeof("ZSCORE") - 1, NULL);
}