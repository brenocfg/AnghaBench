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
typedef  size_t off_t ;

/* Variables and functions */

__attribute__((used)) static bool ath9k_hw_nvram_read_array(u16 *blob, size_t blob_size,
				      off_t offset, u16 *data)
{
	if (offset >= blob_size)
		return false;

	*data =  blob[offset];
	return true;
}