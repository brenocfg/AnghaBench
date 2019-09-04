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
#define  TPACKET_V1 129 
#define  TPACKET_V2 128 
 int /*<<< orphan*/  __v1_rx_user_ready (void*) ; 
 int /*<<< orphan*/  __v2_rx_user_ready (void*) ; 

__attribute__((used)) static inline void __v1_v2_rx_user_ready(void *base, int version)
{
	switch (version) {
	case TPACKET_V1:
		__v1_rx_user_ready(base);
		break;
	case TPACKET_V2:
		__v2_rx_user_ready(base);
		break;
	}
}