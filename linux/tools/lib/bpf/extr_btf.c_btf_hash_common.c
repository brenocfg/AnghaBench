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
struct btf_type {int /*<<< orphan*/  size; int /*<<< orphan*/  info; int /*<<< orphan*/  name_off; } ;

/* Variables and functions */
 long hash_combine (long,int /*<<< orphan*/ ) ; 

__attribute__((used)) static long btf_hash_common(struct btf_type *t)
{
	long h;

	h = hash_combine(0, t->name_off);
	h = hash_combine(h, t->info);
	h = hash_combine(h, t->size);
	return h;
}