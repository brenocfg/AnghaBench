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
struct btf_type {int name_off; int info; int size; } ;

/* Variables and functions */
 long hash_combine (long,int) ; 

__attribute__((used)) static long btf_hash_enum(struct btf_type *t)
{
	long h;

	/* don't hash vlen and enum members to support enum fwd resolving */
	h = hash_combine(0, t->name_off);
	h = hash_combine(h, t->info & ~0xffff);
	h = hash_combine(h, t->size);
	return h;
}