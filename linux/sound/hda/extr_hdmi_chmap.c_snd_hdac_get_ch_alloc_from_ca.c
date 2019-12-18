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
struct hdac_cea_channel_speaker_allocation {int dummy; } ;

/* Variables and functions */
 struct hdac_cea_channel_speaker_allocation* channel_allocations ; 
 size_t get_channel_allocation_order (int) ; 

struct hdac_cea_channel_speaker_allocation *snd_hdac_get_ch_alloc_from_ca(int ca)
{
	return &channel_allocations[get_channel_allocation_order(ca)];
}