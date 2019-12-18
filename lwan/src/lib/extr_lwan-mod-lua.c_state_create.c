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
struct lwan_lua_state {int /*<<< orphan*/  L; } ;
struct lwan_lua_priv {int /*<<< orphan*/  script; int /*<<< orphan*/  script_file; } ;
struct cache_entry {int dummy; } ;

/* Variables and functions */
 scalar_t__ LIKELY (int /*<<< orphan*/ ) ; 
 scalar_t__ UNLIKELY (int) ; 
 int /*<<< orphan*/  free (struct lwan_lua_state*) ; 
 int /*<<< orphan*/  lwan_lua_create_state (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct lwan_lua_state* malloc (int) ; 

__attribute__((used)) static struct cache_entry *state_create(const char *key __attribute__((unused)),
                                        void *context)
{
    struct lwan_lua_priv *priv = context;
    struct lwan_lua_state *state = malloc(sizeof(*state));

    if (UNLIKELY(!state))
        return NULL;

    state->L = lwan_lua_create_state(priv->script_file, priv->script);
    if (LIKELY(state->L))
        return (struct cache_entry *)state;

    free(state);
    return NULL;
}