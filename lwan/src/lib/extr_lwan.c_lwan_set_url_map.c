#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct lwan_url_map {int /*<<< orphan*/  flags; TYPE_1__* module; int /*<<< orphan*/  handler; int /*<<< orphan*/  args; scalar_t__ prefix; int /*<<< orphan*/  data; } ;
struct lwan {int /*<<< orphan*/  url_map_trie; } ;
struct TYPE_2__ {int /*<<< orphan*/  handle_request; int /*<<< orphan*/  flags; int /*<<< orphan*/  (* create ) (scalar_t__,int /*<<< orphan*/ ) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  HANDLER_PARSE_MASK ; 
 scalar_t__ UNLIKELY (int) ; 
 struct lwan_url_map* add_url_map (int /*<<< orphan*/ *,int /*<<< orphan*/ *,struct lwan_url_map const*) ; 
 int /*<<< orphan*/  destroy_urlmap ; 
 int /*<<< orphan*/  lwan_status_critical_perror (char*) ; 
 int /*<<< orphan*/  lwan_trie_destroy (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  lwan_trie_init (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub1 (scalar_t__,int /*<<< orphan*/ ) ; 

void lwan_set_url_map(struct lwan *l, const struct lwan_url_map *map)
{
    lwan_trie_destroy(&l->url_map_trie);
    if (UNLIKELY(!lwan_trie_init(&l->url_map_trie, destroy_urlmap)))
        lwan_status_critical_perror("Could not initialize trie");

    for (; map->prefix; map++) {
        struct lwan_url_map *copy = add_url_map(&l->url_map_trie, NULL, map);

        if (copy->module && copy->module->create) {
            copy->data = copy->module->create (map->prefix, copy->args);
            copy->flags = copy->module->flags;
            copy->handler = copy->module->handle_request;
        } else {
            copy->flags = HANDLER_PARSE_MASK;
        }
    }
}