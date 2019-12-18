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
struct lwan_lua_settings {int /*<<< orphan*/  script; int /*<<< orphan*/  cache_period; int /*<<< orphan*/  script_file; int /*<<< orphan*/  default_type; } ;
struct hash {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  hash_find (struct hash const*,char*) ; 
 void* lua_create (char const*,struct lwan_lua_settings*) ; 
 int /*<<< orphan*/  parse_time_period (int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void *lua_create_from_hash(const char *prefix, const struct hash *hash)
{
    struct lwan_lua_settings settings = {
        .default_type = hash_find(hash, "default_type"),
        .script_file = hash_find(hash, "script_file"),
        .cache_period = parse_time_period(hash_find(hash, "cache_period"), 15),
        .script = hash_find(hash, "script")
    };

    return lua_create(prefix, &settings);
}