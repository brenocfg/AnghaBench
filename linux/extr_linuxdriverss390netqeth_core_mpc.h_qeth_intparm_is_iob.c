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
#define  QETH_CLEAR_CHANNEL_PARM 130 
#define  QETH_HALT_CHANNEL_PARM 129 
#define  QETH_RCD_PARM 128 

__attribute__((used)) static inline bool qeth_intparm_is_iob(unsigned long intparm)
{
	switch (intparm) {
	case QETH_CLEAR_CHANNEL_PARM:
	case QETH_HALT_CHANNEL_PARM:
	case QETH_RCD_PARM:
	case 0:
		return false;
	}
	return true;
}