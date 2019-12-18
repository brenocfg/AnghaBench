#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_5__ ;
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int /*<<< orphan*/  b; } ;
struct TYPE_7__ {TYPE_1__ b; } ;
struct TYPE_8__ {int /*<<< orphan*/  a; } ;
struct TYPE_9__ {TYPE_3__ a; } ;
struct core_reloc_nesting {TYPE_2__ b; TYPE_4__ a; } ;
struct TYPE_10__ {int /*<<< orphan*/  out; int /*<<< orphan*/  in; } ;

/* Variables and functions */
 scalar_t__ BPF_CORE_READ (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 TYPE_5__ data ; 

int test_core_nesting(void *ctx)
{
	struct core_reloc_nesting *in = (void *)&data.in;
	struct core_reloc_nesting *out = (void *)&data.out;

	if (BPF_CORE_READ(&out->a.a.a, &in->a.a.a))
		return 1;
	if (BPF_CORE_READ(&out->b.b.b, &in->b.b.b))
		return 1;

	return 0;
}