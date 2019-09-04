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
struct nsim_map_entry {scalar_t__ key; } ;
struct bpf_map {int /*<<< orphan*/  key_size; } ;

/* Variables and functions */
 int /*<<< orphan*/  memcmp (void*,scalar_t__,int /*<<< orphan*/ ) ; 

__attribute__((used)) static bool
nsim_map_key_match(struct bpf_map *map, struct nsim_map_entry *e, void *key)
{
	return e->key && !memcmp(key, e->key, map->key_size);
}