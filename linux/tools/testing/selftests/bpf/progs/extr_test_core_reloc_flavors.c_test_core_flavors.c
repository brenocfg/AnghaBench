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
struct core_reloc_flavors___weird {int /*<<< orphan*/  a; } ;
struct core_reloc_flavors___reversed {int /*<<< orphan*/  b; } ;
struct core_reloc_flavors {int /*<<< orphan*/  c; int /*<<< orphan*/  b; int /*<<< orphan*/  a; } ;
struct TYPE_2__ {int /*<<< orphan*/  out; int /*<<< orphan*/  in; } ;

/* Variables and functions */
 scalar_t__ BPF_CORE_READ (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 TYPE_1__ data ; 

int test_core_flavors(void *ctx)
{
	struct core_reloc_flavors *in_orig = (void *)&data.in;
	struct core_reloc_flavors___reversed *in_rev = (void *)&data.in;
	struct core_reloc_flavors___weird *in_weird = (void *)&data.in;
	struct core_reloc_flavors *out = (void *)&data.out;

	/* read a using weird layout */
	if (BPF_CORE_READ(&out->a, &in_weird->a))
		return 1;
	/* read b using reversed layout */
	if (BPF_CORE_READ(&out->b, &in_rev->b))
		return 1;
	/* read c using original layout */
	if (BPF_CORE_READ(&out->c, &in_orig->c))
		return 1;

	return 0;
}