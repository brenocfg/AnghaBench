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
struct core_reloc_ints {int /*<<< orphan*/  s64_field; int /*<<< orphan*/  u64_field; int /*<<< orphan*/  s32_field; int /*<<< orphan*/  u32_field; int /*<<< orphan*/  s16_field; int /*<<< orphan*/  u16_field; int /*<<< orphan*/  s8_field; int /*<<< orphan*/  u8_field; } ;
struct TYPE_2__ {int /*<<< orphan*/  out; int /*<<< orphan*/  in; } ;

/* Variables and functions */
 scalar_t__ BPF_CORE_READ (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 TYPE_1__ data ; 

int test_core_ints(void *ctx)
{
	struct core_reloc_ints *in = (void *)&data.in;
	struct core_reloc_ints *out = (void *)&data.out;

	if (BPF_CORE_READ(&out->u8_field, &in->u8_field) ||
	    BPF_CORE_READ(&out->s8_field, &in->s8_field) ||
	    BPF_CORE_READ(&out->u16_field, &in->u16_field) ||
	    BPF_CORE_READ(&out->s16_field, &in->s16_field) ||
	    BPF_CORE_READ(&out->u32_field, &in->u32_field) ||
	    BPF_CORE_READ(&out->s32_field, &in->s32_field) ||
	    BPF_CORE_READ(&out->u64_field, &in->u64_field) ||
	    BPF_CORE_READ(&out->s64_field, &in->s64_field))
		return 1;

	return 0;
}