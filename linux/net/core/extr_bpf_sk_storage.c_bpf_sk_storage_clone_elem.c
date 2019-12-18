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
struct sock {int dummy; } ;
struct bpf_sk_storage_map {int /*<<< orphan*/  map; } ;
struct bpf_sk_storage_elem {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  data; } ;

/* Variables and functions */
 TYPE_1__* SDATA (struct bpf_sk_storage_elem*) ; 
 int /*<<< orphan*/  copy_map_value (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  copy_map_value_locked (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 scalar_t__ map_value_has_spin_lock (int /*<<< orphan*/ *) ; 
 struct bpf_sk_storage_elem* selem_alloc (struct bpf_sk_storage_map*,struct sock*,int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static struct bpf_sk_storage_elem *
bpf_sk_storage_clone_elem(struct sock *newsk,
			  struct bpf_sk_storage_map *smap,
			  struct bpf_sk_storage_elem *selem)
{
	struct bpf_sk_storage_elem *copy_selem;

	copy_selem = selem_alloc(smap, newsk, NULL, true);
	if (!copy_selem)
		return NULL;

	if (map_value_has_spin_lock(&smap->map))
		copy_map_value_locked(&smap->map, SDATA(copy_selem)->data,
				      SDATA(selem)->data, true);
	else
		copy_map_value(&smap->map, SDATA(copy_selem)->data,
			       SDATA(selem)->data);

	return copy_selem;
}