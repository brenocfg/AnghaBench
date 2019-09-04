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
#define  TPACKET_V1 130 
#define  TPACKET_V2 129 
#define  TPACKET_V3 128 
 int __v1_tx_kernel_ready (void*) ; 
 int __v2_tx_kernel_ready (void*) ; 
 int __v3_tx_kernel_ready (void*) ; 
 int /*<<< orphan*/  bug_on (int) ; 

__attribute__((used)) static inline int __tx_kernel_ready(void *base, int version)
{
	switch (version) {
	case TPACKET_V1:
		return __v1_tx_kernel_ready(base);
	case TPACKET_V2:
		return __v2_tx_kernel_ready(base);
	case TPACKET_V3:
		return __v3_tx_kernel_ready(base);
	default:
		bug_on(1);
		return 0;
	}
}