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
struct btf_type {scalar_t__ name_off; scalar_t__ info; scalar_t__ size; } ;

/* Variables and functions */

__attribute__((used)) static bool btf_equal_common(struct btf_type *t1, struct btf_type *t2)
{
	return t1->name_off == t2->name_off &&
	       t1->info == t2->info &&
	       t1->size == t2->size;
}