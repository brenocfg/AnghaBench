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
struct core_reloc_misc_output {int /*<<< orphan*/  c; int /*<<< orphan*/  b; int /*<<< orphan*/  a; } ;
struct core_reloc_misc_extensible {int dummy; } ;
struct core_reloc_misc___b {struct core_reloc_misc_extensible b1; } ;
struct core_reloc_misc___a {struct core_reloc_misc_extensible a1; } ;
struct TYPE_2__ {int /*<<< orphan*/  out; int /*<<< orphan*/  in; } ;

/* Variables and functions */
 scalar_t__ BPF_CORE_READ (int /*<<< orphan*/ *,struct core_reloc_misc_extensible*) ; 
 TYPE_1__ data ; 

int test_core_misc(void *ctx)
{
	struct core_reloc_misc___a *in_a = (void *)&data.in;
	struct core_reloc_misc___b *in_b = (void *)&data.in;
	struct core_reloc_misc_extensible *in_ext = (void *)&data.in;
	struct core_reloc_misc_output *out = (void *)&data.out;

	/* record two different relocations with the same accessor string */
	if (BPF_CORE_READ(&out->a, &in_a->a1) ||	/* accessor: 0:0 */
	    BPF_CORE_READ(&out->b, &in_b->b1))		/* accessor: 0:0 */
		return 1;

	/* Validate relocations capture array-only accesses for structs with
	 * fixed header, but with potentially extendable tail. This will read
	 * first 4 bytes of 2nd element of in_ext array of potentially
	 * variably sized struct core_reloc_misc_extensible. */ 
	if (BPF_CORE_READ(&out->c, &in_ext[2]))		/* accessor: 2 */
		return 1;

	return 0;
}