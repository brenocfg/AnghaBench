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
#define  A10SR_RESET_BQSPI 132 
#define  A10SR_RESET_ENET_HPS 131 
#define  A10SR_RESET_FILE 130 
#define  A10SR_RESET_PCIE 129 
#define  A10SR_RESET_USB 128 
 int EINVAL ; 

__attribute__((used)) static inline int a10sr_reset_shift(unsigned long id)
{
	switch (id) {
	case A10SR_RESET_ENET_HPS:
		return 1;
	case A10SR_RESET_PCIE:
	case A10SR_RESET_FILE:
	case A10SR_RESET_BQSPI:
	case A10SR_RESET_USB:
		return id + 11;
	default:
		return -EINVAL;
	}
}