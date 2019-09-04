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
typedef  int u16 ;

/* Variables and functions */
#define  STAT_ASSOC 138 
#define  STAT_ASSOC_FAIL 137 
#define  STAT_AUTH_FAIL 136 
#define  STAT_DEAUTH 135 
#define  STAT_DISASSOC 134 
#define  STAT_FORCELOSS 133 
#define  STAT_MAXARL 132 
#define  STAT_MAXRETRIES 131 
#define  STAT_NOBEACON 130 
#define  STAT_REASSOC 129 
#define  STAT_TSFSYNC 128 
 int /*<<< orphan*/  airo_print_dbg (char const*,char*,...) ; 

__attribute__((used)) static void airo_print_status(const char *devname, u16 status)
{
	u8 reason = status & 0xFF;

	switch (status & 0xFF00) {
	case STAT_NOBEACON:
		switch (status) {
		case STAT_NOBEACON:
			airo_print_dbg(devname, "link lost (missed beacons)");
			break;
		case STAT_MAXRETRIES:
		case STAT_MAXARL:
			airo_print_dbg(devname, "link lost (max retries)");
			break;
		case STAT_FORCELOSS:
			airo_print_dbg(devname, "link lost (local choice)");
			break;
		case STAT_TSFSYNC:
			airo_print_dbg(devname, "link lost (TSF sync lost)");
			break;
		default:
			airo_print_dbg(devname, "unknown status %x\n", status);
			break;
		}
		break;
	case STAT_DEAUTH:
		airo_print_dbg(devname, "deauthenticated (reason: %d)", reason);
		break;
	case STAT_DISASSOC:
		airo_print_dbg(devname, "disassociated (reason: %d)", reason);
		break;
	case STAT_ASSOC_FAIL:
		airo_print_dbg(devname, "association failed (reason: %d)",
			       reason);
		break;
	case STAT_AUTH_FAIL:
		airo_print_dbg(devname, "authentication failed (reason: %d)",
			       reason);
		break;
	case STAT_ASSOC:
	case STAT_REASSOC:
		break;
	default:
		airo_print_dbg(devname, "unknown status %x\n", status);
		break;
	}
}