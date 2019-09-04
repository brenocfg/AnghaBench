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
struct TYPE_2__ {char obj_type; int /*<<< orphan*/  obj_index; scalar_t__ read_only; scalar_t__ spare; int /*<<< orphan*/  adapter_index; } ;
union handle_word {int /*<<< orphan*/  w; TYPE_1__ h; } ;
typedef  int /*<<< orphan*/  u32 ;
typedef  int /*<<< orphan*/  u16 ;

/* Variables and functions */

u32 hpi_indexes_to_handle(const char c_object, const u16 adapter_index,
	const u16 object_index)
{
	union handle_word handle;

	handle.h.adapter_index = adapter_index;
	handle.h.spare = 0;
	handle.h.read_only = 0;
	handle.h.obj_type = c_object;
	handle.h.obj_index = object_index;
	return handle.w;
}