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
#define  WCD_CLSH_STATE_EAR 132 
#define  WCD_CLSH_STATE_HPHL 131 
#define  WCD_CLSH_STATE_HPHR 130 
#define  WCD_CLSH_STATE_IDLE 129 
#define  WCD_CLSH_STATE_LO 128 

__attribute__((used)) static bool wcd_clsh_is_state_valid(int state)
{
	switch (state) {
	case WCD_CLSH_STATE_IDLE:
	case WCD_CLSH_STATE_EAR:
	case WCD_CLSH_STATE_HPHL:
	case WCD_CLSH_STATE_HPHR:
	case WCD_CLSH_STATE_LO:
		return true;
	default:
		return false;
	};
}