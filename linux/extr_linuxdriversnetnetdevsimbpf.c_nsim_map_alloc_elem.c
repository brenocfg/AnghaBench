#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct nsim_bpf_bound_map {TYPE_2__* entry; } ;
struct TYPE_3__ {int /*<<< orphan*/  value_size; int /*<<< orphan*/  key_size; } ;
struct bpf_offloaded_map {TYPE_1__ map; struct nsim_bpf_bound_map* dev_priv; } ;
struct TYPE_4__ {int /*<<< orphan*/ * key; void* value; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_USER ; 
 int /*<<< orphan*/  kfree (int /*<<< orphan*/ *) ; 
 void* kmalloc (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
nsim_map_alloc_elem(struct bpf_offloaded_map *offmap, unsigned int idx)
{
	struct nsim_bpf_bound_map *nmap = offmap->dev_priv;

	nmap->entry[idx].key = kmalloc(offmap->map.key_size, GFP_USER);
	if (!nmap->entry[idx].key)
		return -ENOMEM;
	nmap->entry[idx].value = kmalloc(offmap->map.value_size, GFP_USER);
	if (!nmap->entry[idx].value) {
		kfree(nmap->entry[idx].key);
		nmap->entry[idx].key = NULL;
		return -ENOMEM;
	}

	return 0;
}