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
typedef  union bpf_attr {int dummy; } bpf_attr ;
struct bpf_map {int dummy; } ;
struct bpf_dtab {struct bpf_map map; int /*<<< orphan*/  list; } ;

/* Variables and functions */
 int /*<<< orphan*/  CAP_NET_ADMIN ; 
 int ENOMEM ; 
 int EPERM ; 
 struct bpf_map* ERR_PTR (int) ; 
 int /*<<< orphan*/  GFP_USER ; 
 int /*<<< orphan*/  capable (int /*<<< orphan*/ ) ; 
 int dev_map_init_map (struct bpf_dtab*,union bpf_attr*) ; 
 int /*<<< orphan*/  dev_map_list ; 
 int /*<<< orphan*/  dev_map_lock ; 
 int /*<<< orphan*/  kfree (struct bpf_dtab*) ; 
 struct bpf_dtab* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  list_add_tail_rcu (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static struct bpf_map *dev_map_alloc(union bpf_attr *attr)
{
	struct bpf_dtab *dtab;
	int err;

	if (!capable(CAP_NET_ADMIN))
		return ERR_PTR(-EPERM);

	dtab = kzalloc(sizeof(*dtab), GFP_USER);
	if (!dtab)
		return ERR_PTR(-ENOMEM);

	err = dev_map_init_map(dtab, attr);
	if (err) {
		kfree(dtab);
		return ERR_PTR(err);
	}

	spin_lock(&dev_map_lock);
	list_add_tail_rcu(&dtab->list, &dev_map_list);
	spin_unlock(&dev_map_lock);

	return &dtab->map;
}