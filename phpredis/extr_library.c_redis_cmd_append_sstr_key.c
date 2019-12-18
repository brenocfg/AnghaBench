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
typedef  int /*<<< orphan*/  smart_string ;
typedef  int /*<<< orphan*/  RedisSock ;

/* Variables and functions */
 short cluster_hash_key (char*,size_t) ; 
 int /*<<< orphan*/  efree (char*) ; 
 int redis_cmd_append_sstr (int /*<<< orphan*/ *,char*,size_t) ; 
 int redis_key_prefix (int /*<<< orphan*/ *,char**,size_t*) ; 

int redis_cmd_append_sstr_key(smart_string *str, char *key, size_t len, RedisSock *redis_sock, short *slot) {
    int valfree, retval;

    valfree = redis_key_prefix(redis_sock, &key, &len);
    if (slot) *slot = cluster_hash_key(key, len);
    retval = redis_cmd_append_sstr(str, key, len);
    if (valfree) efree(key);

    return retval;
}