#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct core_reloc_arrays_output {int /*<<< orphan*/  d00d; int /*<<< orphan*/  c1c; int /*<<< orphan*/  b123; int /*<<< orphan*/  a2; } ;
struct core_reloc_arrays {TYPE_2__** d; TYPE_1__* c; int /*<<< orphan*/ *** b; int /*<<< orphan*/ * a; } ;
struct TYPE_6__ {int /*<<< orphan*/  out; int /*<<< orphan*/  in; } ;
struct TYPE_5__ {int /*<<< orphan*/  d; } ;
struct TYPE_4__ {int /*<<< orphan*/  c; } ;

/* Variables and functions */
 scalar_t__ BPF_CORE_READ (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 TYPE_3__ data ; 

int test_core_arrays(void *ctx)
{
	struct core_reloc_arrays *in = (void *)&data.in;
	struct core_reloc_arrays_output *out = (void *)&data.out;

	/* in->a[2] */
	if (BPF_CORE_READ(&out->a2, &in->a[2]))
		return 1;
	/* in->b[1][2][3] */
	if (BPF_CORE_READ(&out->b123, &in->b[1][2][3]))
		return 1;
	/* in->c[1].c */
	if (BPF_CORE_READ(&out->c1c, &in->c[1].c))
		return 1;
	/* in->d[0][0].d */
	if (BPF_CORE_READ(&out->d00d, &in->d[0][0].d))
		return 1;

	return 0;
}