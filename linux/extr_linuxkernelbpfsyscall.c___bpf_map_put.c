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
struct bpf_map {int /*<<< orphan*/  work; int /*<<< orphan*/  btf; int /*<<< orphan*/  refcnt; } ;

/* Variables and functions */
 int /*<<< orphan*/  INIT_WORK (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 scalar_t__ atomic_dec_and_test (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  bpf_map_free_deferred ; 
 int /*<<< orphan*/  bpf_map_free_id (struct bpf_map*,int) ; 
 int /*<<< orphan*/  btf_put (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  schedule_work (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void __bpf_map_put(struct bpf_map *map, bool do_idr_lock)
{
	if (atomic_dec_and_test(&map->refcnt)) {
		/* bpf_map_free_id() must be called first */
		bpf_map_free_id(map, do_idr_lock);
		btf_put(map->btf);
		INIT_WORK(&map->work, bpf_map_free_deferred);
		schedule_work(&map->work);
	}
}