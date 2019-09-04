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
typedef  int u8 ;
typedef  size_t u16 ;

/* Variables and functions */
 int PK_TYPE_11A ; 
 size_t RATE_54M ; 
 scalar_t__* vnt_frame_time ; 

unsigned int vnt_get_frame_time(u8 preamble_type, u8 pkt_type,
				unsigned int frame_length, u16 tx_rate)
{
	unsigned int frame_time;
	unsigned int preamble;
	unsigned int tmp;
	unsigned int rate = 0;

	if (tx_rate > RATE_54M)
		return 0;

	rate = (unsigned int)vnt_frame_time[tx_rate];

	if (tx_rate <= 3) {
		if (preamble_type == 1)
			preamble = 96;
		else
			preamble = 192;

		frame_time = (frame_length * 80) / rate;
		tmp = (frame_time * rate) / 80;

		if (frame_length != tmp)
			frame_time++;

		return preamble + frame_time;
	}
	frame_time = (frame_length * 8 + 22) / rate;
	tmp = ((frame_time * rate) - 22) / 8;

	if (frame_length != tmp)
		frame_time++;

	frame_time = frame_time * 4;

	if (pkt_type != PK_TYPE_11A)
		frame_time += 6;
	return 20 + frame_time;
}