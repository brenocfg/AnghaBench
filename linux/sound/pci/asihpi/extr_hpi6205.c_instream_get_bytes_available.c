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
typedef  scalar_t__ u32 ;
struct hpi_hostbuffer_status {scalar_t__ host_index; scalar_t__ dsp_index; } ;

/* Variables and functions */

__attribute__((used)) static u32 instream_get_bytes_available(struct hpi_hostbuffer_status *status)
{
	return status->dsp_index - status->host_index;
}