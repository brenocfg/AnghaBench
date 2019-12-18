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
typedef  scalar_t__ zend_bool ;

/* Variables and functions */
 int /*<<< orphan*/  MULTI ; 
#define  REDIS_HASH 132 
#define  REDIS_LIST 131 
#define  REDIS_SET 130 
#define  REDIS_STRING 129 
#define  REDIS_ZSET 128 
 int /*<<< orphan*/  ra_del_key (char const*,int,int /*<<< orphan*/ *) ; 
 scalar_t__ ra_get_key_type (int /*<<< orphan*/ *,char const*,int,int /*<<< orphan*/ *,long*) ; 
 int /*<<< orphan*/  ra_index_exec (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ra_index_key (char const*,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ra_index_multi (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 scalar_t__ ra_move_hash (char const*,int,int /*<<< orphan*/ *,int /*<<< orphan*/ *,long) ; 
 scalar_t__ ra_move_list (char const*,int,int /*<<< orphan*/ *,int /*<<< orphan*/ *,long) ; 
 scalar_t__ ra_move_set (char const*,int,int /*<<< orphan*/ *,int /*<<< orphan*/ *,long) ; 
 scalar_t__ ra_move_string (char const*,int,int /*<<< orphan*/ *,int /*<<< orphan*/ *,long) ; 
 scalar_t__ ra_move_zset (char const*,int,int /*<<< orphan*/ *,int /*<<< orphan*/ *,long) ; 

void
ra_move_key(const char *key, int key_len, zval *z_from, zval *z_to) {

    long res[2] = {0}, type, ttl;
    zend_bool success = 0;
    if (ra_get_key_type(z_from, key, key_len, z_from, res)) {
        type = res[0];
        ttl = res[1];
        /* open transaction on target server */
        ra_index_multi(z_to, MULTI);
        switch(type) {
            case REDIS_STRING:
                success = ra_move_string(key, key_len, z_from, z_to, ttl);
                break;

            case REDIS_SET:
                success = ra_move_set(key, key_len, z_from, z_to, ttl);
                break;

            case REDIS_LIST:
                success = ra_move_list(key, key_len, z_from, z_to, ttl);
                break;

            case REDIS_ZSET:
                success = ra_move_zset(key, key_len, z_from, z_to, ttl);
                break;

            case REDIS_HASH:
                success = ra_move_hash(key, key_len, z_from, z_to, ttl);
                break;

            default:
                /* TODO: report? */
                break;
        }
    }

    if(success) {
        ra_del_key(key, key_len, z_from);
        ra_index_key(key, key_len, z_to);
    }

    /* close transaction */
    ra_index_exec(z_to, NULL, 0);
}