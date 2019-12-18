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
struct core_reloc_ptr_as_arr {int /*<<< orphan*/  a; } ;
struct TYPE_2__ {int /*<<< orphan*/  out; int /*<<< orphan*/  in; } ;

/* Variables and functions */
 scalar_t__ BPF_CORE_READ (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 TYPE_1__ data ; 

int test_core_ptr_as_arr(void *ctx)
{
	struct core_reloc_ptr_as_arr *in = (void *)&data.in;
	struct core_reloc_ptr_as_arr *out = (void *)&data.out;

	if (BPF_CORE_READ(&out->a, &in[2].a))
		return 1;

	return 0;
}