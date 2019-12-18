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
struct sock {int /*<<< orphan*/  sk_omem_alloc; } ;
struct TYPE_3__ {int /*<<< orphan*/  value_size; } ;
struct bpf_sk_storage_map {int /*<<< orphan*/  elem_size; TYPE_1__ map; } ;
struct bpf_sk_storage_elem {int dummy; } ;
struct TYPE_4__ {int /*<<< orphan*/  data; } ;

/* Variables and functions */
 int GFP_ATOMIC ; 
 TYPE_2__* SDATA (struct bpf_sk_storage_elem*) ; 
 int __GFP_NOWARN ; 
 int /*<<< orphan*/  atomic_sub (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 struct bpf_sk_storage_elem* kzalloc (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,void*,int /*<<< orphan*/ ) ; 
 scalar_t__ omem_charge (struct sock*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static struct bpf_sk_storage_elem *selem_alloc(struct bpf_sk_storage_map *smap,
					       struct sock *sk, void *value,
					       bool charge_omem)
{
	struct bpf_sk_storage_elem *selem;

	if (charge_omem && omem_charge(sk, smap->elem_size))
		return NULL;

	selem = kzalloc(smap->elem_size, GFP_ATOMIC | __GFP_NOWARN);
	if (selem) {
		if (value)
			memcpy(SDATA(selem)->data, value, smap->map.value_size);
		return selem;
	}

	if (charge_omem)
		atomic_sub(smap->elem_size, &sk->sk_omem_alloc);

	return NULL;
}