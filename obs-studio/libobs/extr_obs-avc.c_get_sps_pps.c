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
typedef  int uint8_t ;

/* Variables and functions */
 int OBS_NAL_PPS ; 
 int OBS_NAL_SPS ; 
 int* obs_avc_find_startcode (int const*,int const*) ; 

__attribute__((used)) static void get_sps_pps(const uint8_t *data, size_t size, const uint8_t **sps,
			size_t *sps_size, const uint8_t **pps, size_t *pps_size)
{
	const uint8_t *nal_start, *nal_end;
	const uint8_t *end = data + size;
	int type;

	nal_start = obs_avc_find_startcode(data, end);
	while (true) {
		while (nal_start < end && !*(nal_start++))
			;

		if (nal_start == end)
			break;

		nal_end = obs_avc_find_startcode(nal_start, end);

		type = nal_start[0] & 0x1F;
		if (type == OBS_NAL_SPS) {
			*sps = nal_start;
			*sps_size = nal_end - nal_start;
		} else if (type == OBS_NAL_PPS) {
			*pps = nal_start;
			*pps_size = nal_end - nal_start;
		}

		nal_start = nal_end;
	}
}