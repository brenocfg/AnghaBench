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
struct bpf_map {int /*<<< orphan*/  usercnt; int /*<<< orphan*/  refcnt; } ;

/* Variables and functions */
 scalar_t__ BPF_MAX_REFCNT ; 
 int /*<<< orphan*/  EBUSY ; 
 struct bpf_map* ERR_PTR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  atomic_dec (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  atomic_inc (int /*<<< orphan*/ *) ; 
 scalar_t__ atomic_inc_return (int /*<<< orphan*/ *) ; 

struct bpf_map *bpf_map_inc(struct bpf_map *map, bool uref)
{
	if (atomic_inc_return(&map->refcnt) > BPF_MAX_REFCNT) {
		atomic_dec(&map->refcnt);
		return ERR_PTR(-EBUSY);
	}
	if (uref)
		atomic_inc(&map->usercnt);
	return map;
}