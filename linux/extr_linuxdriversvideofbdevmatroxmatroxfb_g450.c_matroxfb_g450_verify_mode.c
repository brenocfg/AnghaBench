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
typedef  int u_int32_t ;

/* Variables and functions */
 int EINVAL ; 
#define  MATROXFB_OUTPUT_MODE_MONITOR 130 
#define  MATROXFB_OUTPUT_MODE_NTSC 129 
#define  MATROXFB_OUTPUT_MODE_PAL 128 

__attribute__((used)) static int matroxfb_g450_verify_mode(void* md, u_int32_t arg) {
	switch (arg) {
		case MATROXFB_OUTPUT_MODE_PAL:
		case MATROXFB_OUTPUT_MODE_NTSC:
		case MATROXFB_OUTPUT_MODE_MONITOR:
			return 0;
	}
	return -EINVAL;
}