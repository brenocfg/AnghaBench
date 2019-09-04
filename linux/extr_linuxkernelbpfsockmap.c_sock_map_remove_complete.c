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
struct bpf_stab {int /*<<< orphan*/  sock_map; } ;

/* Variables and functions */
 int /*<<< orphan*/  bpf_map_area_free (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree (struct bpf_stab*) ; 

__attribute__((used)) static void sock_map_remove_complete(struct bpf_stab *stab)
{
	bpf_map_area_free(stab->sock_map);
	kfree(stab);
}