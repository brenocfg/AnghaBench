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
typedef  int s16 ;
typedef  enum CHANNEL_WIDTH { ____Placeholder_CHANNEL_WIDTH } CHANNEL_WIDTH ;

/* Variables and functions */
#define  CHANNEL_WIDTH_160 131 
#define  CHANNEL_WIDTH_20 130 
#define  CHANNEL_WIDTH_40 129 
#define  CHANNEL_WIDTH_80 128 

__attribute__((used)) static s16 get_bandwidth_idx(const enum CHANNEL_WIDTH bandwidth)
{
	switch (bandwidth) {
	case CHANNEL_WIDTH_20:
		return 0;
	case CHANNEL_WIDTH_40:
		return 1;
	case CHANNEL_WIDTH_80:
		return 2;
	case CHANNEL_WIDTH_160:
		return 3;
	default:
		return -1;
	}
}