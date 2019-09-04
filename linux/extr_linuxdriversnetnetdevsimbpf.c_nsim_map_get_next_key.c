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
struct nsim_bpf_bound_map {TYPE_2__* entry; int /*<<< orphan*/  mutex; } ;
struct TYPE_3__ {int /*<<< orphan*/  key_size; } ;
struct bpf_offloaded_map {TYPE_1__ map; struct nsim_bpf_bound_map* dev_priv; } ;
struct TYPE_4__ {scalar_t__ key; } ;

/* Variables and functions */
 int ARRAY_SIZE (TYPE_2__*) ; 
 int ENOENT ; 
 int /*<<< orphan*/  memcpy (void*,scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int nsim_map_key_find (struct bpf_offloaded_map*,void*) ; 

__attribute__((used)) static int
nsim_map_get_next_key(struct bpf_offloaded_map *offmap,
		      void *key, void *next_key)
{
	struct nsim_bpf_bound_map *nmap = offmap->dev_priv;
	int idx = -ENOENT;

	mutex_lock(&nmap->mutex);

	if (key)
		idx = nsim_map_key_find(offmap, key);
	if (idx == -ENOENT)
		idx = 0;
	else
		idx++;

	for (; idx < ARRAY_SIZE(nmap->entry); idx++) {
		if (nmap->entry[idx].key) {
			memcpy(next_key, nmap->entry[idx].key,
			       offmap->map.key_size);
			break;
		}
	}

	mutex_unlock(&nmap->mutex);

	if (idx == ARRAY_SIZE(nmap->entry))
		return -ENOENT;
	return 0;
}