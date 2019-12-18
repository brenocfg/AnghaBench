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
struct core_reloc_mods_output {int /*<<< orphan*/  h; int /*<<< orphan*/  g; int /*<<< orphan*/  f; int /*<<< orphan*/  e; int /*<<< orphan*/  d; int /*<<< orphan*/  c; int /*<<< orphan*/  b; int /*<<< orphan*/  a; } ;
struct TYPE_5__ {int /*<<< orphan*/  y; } ;
struct TYPE_4__ {int /*<<< orphan*/  x; } ;
struct core_reloc_mods {TYPE_2__ h; TYPE_1__ g; int /*<<< orphan*/ * f; int /*<<< orphan*/ * e; int /*<<< orphan*/  d; int /*<<< orphan*/  c; int /*<<< orphan*/  b; int /*<<< orphan*/  a; } ;
struct TYPE_6__ {int /*<<< orphan*/  out; int /*<<< orphan*/  in; } ;

/* Variables and functions */
 scalar_t__ BPF_CORE_READ (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 TYPE_3__ data ; 

int test_core_mods(void *ctx)
{
	struct core_reloc_mods *in = (void *)&data.in;
	struct core_reloc_mods_output *out = (void *)&data.out;

	if (BPF_CORE_READ(&out->a, &in->a) ||
	    BPF_CORE_READ(&out->b, &in->b) ||
	    BPF_CORE_READ(&out->c, &in->c) ||
	    BPF_CORE_READ(&out->d, &in->d) ||
	    BPF_CORE_READ(&out->e, &in->e[2]) ||
	    BPF_CORE_READ(&out->f, &in->f[1]) ||
	    BPF_CORE_READ(&out->g, &in->g.x) ||
	    BPF_CORE_READ(&out->h, &in->h.y))
		return 1;

	return 0;
}