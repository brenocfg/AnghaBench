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
struct lwan_key_value_array {int dummy; } ;
struct lwan_key_value {char* key; int /*<<< orphan*/ * value; } ;
struct coro {int dummy; } ;
typedef  int /*<<< orphan*/  lua_State ;

/* Variables and functions */
 int /*<<< orphan*/ * coro_strdup (struct coro*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lua_tostring (int /*<<< orphan*/ *,int) ; 
 struct lwan_key_value* lwan_key_value_array_append (struct lwan_key_value_array*) ; 

__attribute__((used)) static bool append_key_value(lua_State *L,
                             struct coro *coro,
                             struct lwan_key_value_array *arr,
                             char *key,
                             int value_index)
{
    struct lwan_key_value *kv;

    kv = lwan_key_value_array_append(arr);
    if (!kv)
        return false;

    kv->key = key;
    kv->value = coro_strdup(coro, lua_tostring(L, value_index));

    return kv->value != NULL;
}