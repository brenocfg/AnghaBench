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
struct btf_var_secinfo {int offset; } ;

/* Variables and functions */

__attribute__((used)) static int compare_vsi_off(const void *_a, const void *_b)
{
	const struct btf_var_secinfo *a = _a;
	const struct btf_var_secinfo *b = _b;

	return a->offset - b->offset;
}