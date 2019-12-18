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
typedef  int /*<<< orphan*/  u32 ;
typedef  int /*<<< orphan*/  u16 ;

/* Variables and functions */
 int /*<<< orphan*/  hpi_handle_indexes (int /*<<< orphan*/  const,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

void hpi_handle_to_indexes(const u32 handle, u16 *pw_adapter_index,
	u16 *pw_object_index)
{
	hpi_handle_indexes(handle, pw_adapter_index, pw_object_index);
}