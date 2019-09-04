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

/* Variables and functions */

__attribute__((used)) static inline void
extract_scp_header(unsigned int header,
		   unsigned int *target_id, unsigned int *source_id,
		   unsigned int *get_flag, unsigned int *req,
		   unsigned int *device_flag, unsigned int *resp_flag,
		   unsigned int *error_flag, unsigned int *data_size)
{
	if (data_size)
		*data_size = (header >> 27) & 0x1f;
	if (error_flag)
		*error_flag = (header >> 26) & 0x01;
	if (resp_flag)
		*resp_flag = (header >> 25) & 0x01;
	if (device_flag)
		*device_flag = (header >> 24) & 0x01;
	if (req)
		*req = (header >> 17) & 0x7f;
	if (get_flag)
		*get_flag = (header >> 16) & 0x01;
	if (source_id)
		*source_id = (header >> 8) & 0xff;
	if (target_id)
		*target_id = header & 0xff;
}