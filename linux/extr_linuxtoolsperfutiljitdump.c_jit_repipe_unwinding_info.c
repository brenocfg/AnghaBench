#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int /*<<< orphan*/  mapped_size; int /*<<< orphan*/  unwinding_size; int /*<<< orphan*/  eh_frame_hdr_size; int /*<<< orphan*/  unwinding_data; } ;
struct TYPE_4__ {scalar_t__ total_size; } ;
union jr_entry {TYPE_1__ unwinding; TYPE_2__ prefix; } ;
typedef  scalar_t__ uint32_t ;
struct jit_buf_desc {void* unwinding_data; int /*<<< orphan*/  unwinding_mapped_size; int /*<<< orphan*/  unwinding_size; int /*<<< orphan*/  eh_frame_hdr_size; } ;

/* Variables and functions */
 void* malloc (scalar_t__) ; 
 int /*<<< orphan*/  memcpy (void*,int /*<<< orphan*/ *,scalar_t__) ; 

__attribute__((used)) static int
jit_repipe_unwinding_info(struct jit_buf_desc *jd, union jr_entry *jr)
{
	void *unwinding_data;
	uint32_t unwinding_data_size;

	if (!(jd && jr))
		return -1;

	unwinding_data_size  = jr->prefix.total_size - sizeof(jr->unwinding);
	unwinding_data = malloc(unwinding_data_size);
	if (!unwinding_data)
		return -1;

	memcpy(unwinding_data, &jr->unwinding.unwinding_data,
	       unwinding_data_size);

	jd->eh_frame_hdr_size = jr->unwinding.eh_frame_hdr_size;
	jd->unwinding_size = jr->unwinding.unwinding_size;
	jd->unwinding_mapped_size = jr->unwinding.mapped_size;
	jd->unwinding_data = unwinding_data;

	return 0;
}