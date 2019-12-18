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
struct btf_dedup {int /*<<< orphan*/ * dedup_table; TYPE_1__* btf; } ;
struct TYPE_2__ {int nr_types; } ;

/* Variables and functions */
 int btf_dedup_ref_type (struct btf_dedup*,int) ; 
 int /*<<< orphan*/  hashmap__free (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int btf_dedup_ref_types(struct btf_dedup *d)
{
	int i, err;

	for (i = 1; i <= d->btf->nr_types; i++) {
		err = btf_dedup_ref_type(d, i);
		if (err < 0)
			return err;
	}
	/* we won't need d->dedup_table anymore */
	hashmap__free(d->dedup_table);
	d->dedup_table = NULL;
	return 0;
}