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
typedef  int /*<<< orphan*/  u16 ;

/* Variables and functions */
 int /*<<< orphan*/  check_bytes_per_frame (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  norm_sync_buffer_size (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

u16 dim_norm_sync_buffer_size(u16 buf_size, u16 bytes_per_frame)
{
	if (!check_bytes_per_frame(bytes_per_frame))
		return 0;

	return norm_sync_buffer_size(buf_size, bytes_per_frame);
}