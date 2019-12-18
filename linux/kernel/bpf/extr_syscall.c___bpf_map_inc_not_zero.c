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
 int BPF_MAX_REFCNT ; 
 int /*<<< orphan*/  EBUSY ; 
 int /*<<< orphan*/  ENOENT ; 
 struct bpf_map* ERR_PTR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  __bpf_map_put (struct bpf_map*,int) ; 
 int atomic_fetch_add_unless (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  atomic_inc (int /*<<< orphan*/ *) ; 

__attribute__((used)) static struct bpf_map *__bpf_map_inc_not_zero(struct bpf_map *map,
					      bool uref)
{
	int refold;

	refold = atomic_fetch_add_unless(&map->refcnt, 1, 0);

	if (refold >= BPF_MAX_REFCNT) {
		__bpf_map_put(map, false);
		return ERR_PTR(-EBUSY);
	}

	if (!refold)
		return ERR_PTR(-ENOENT);

	if (uref)
		atomic_inc(&map->usercnt);

	return map;
}