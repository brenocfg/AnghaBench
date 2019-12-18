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
struct btf_type {scalar_t__ name_off; scalar_t__ info; } ;
struct btf_param {scalar_t__ name_off; } ;
typedef  int __u16 ;

/* Variables and functions */
 struct btf_param* btf_params (struct btf_type*) ; 
 int btf_vlen (struct btf_type*) ; 

__attribute__((used)) static bool btf_compat_fnproto(struct btf_type *t1, struct btf_type *t2)
{
	const struct btf_param *m1, *m2;
	__u16 vlen;
	int i;

	/* skip return type ID */
	if (t1->name_off != t2->name_off || t1->info != t2->info)
		return false;

	vlen = btf_vlen(t1);
	m1 = btf_params(t1);
	m2 = btf_params(t2);
	for (i = 0; i < vlen; i++) {
		if (m1->name_off != m2->name_off)
			return false;
		m1++;
		m2++;
	}
	return true;
}