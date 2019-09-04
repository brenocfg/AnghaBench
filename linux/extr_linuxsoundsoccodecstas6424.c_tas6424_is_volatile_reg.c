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
struct device {int dummy; } ;

/* Variables and functions */
#define  TAS6424_AC_LOAD_DIAG_REP1 139 
#define  TAS6424_AC_LOAD_DIAG_REP2 138 
#define  TAS6424_AC_LOAD_DIAG_REP3 137 
#define  TAS6424_AC_LOAD_DIAG_REP4 136 
#define  TAS6424_CHANNEL_FAULT 135 
#define  TAS6424_CHANNEL_STATE 134 
#define  TAS6424_DC_LOAD_DIAG_REP12 133 
#define  TAS6424_DC_LOAD_DIAG_REP34 132 
#define  TAS6424_DC_LOAD_DIAG_REPLO 131 
#define  TAS6424_GLOB_FAULT1 130 
#define  TAS6424_GLOB_FAULT2 129 
#define  TAS6424_WARN 128 

__attribute__((used)) static bool tas6424_is_volatile_reg(struct device *dev, unsigned int reg)
{
	switch (reg) {
	case TAS6424_DC_LOAD_DIAG_REP12:
	case TAS6424_DC_LOAD_DIAG_REP34:
	case TAS6424_DC_LOAD_DIAG_REPLO:
	case TAS6424_CHANNEL_STATE:
	case TAS6424_CHANNEL_FAULT:
	case TAS6424_GLOB_FAULT1:
	case TAS6424_GLOB_FAULT2:
	case TAS6424_WARN:
	case TAS6424_AC_LOAD_DIAG_REP1:
	case TAS6424_AC_LOAD_DIAG_REP2:
	case TAS6424_AC_LOAD_DIAG_REP3:
	case TAS6424_AC_LOAD_DIAG_REP4:
		return true;
	default:
		return false;
	}
}