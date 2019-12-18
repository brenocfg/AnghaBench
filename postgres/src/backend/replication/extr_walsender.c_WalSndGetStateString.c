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
typedef  int WalSndState ;

/* Variables and functions */
#define  WALSNDSTATE_BACKUP 132 
#define  WALSNDSTATE_CATCHUP 131 
#define  WALSNDSTATE_STARTUP 130 
#define  WALSNDSTATE_STOPPING 129 
#define  WALSNDSTATE_STREAMING 128 

__attribute__((used)) static const char *
WalSndGetStateString(WalSndState state)
{
	switch (state)
	{
		case WALSNDSTATE_STARTUP:
			return "startup";
		case WALSNDSTATE_BACKUP:
			return "backup";
		case WALSNDSTATE_CATCHUP:
			return "catchup";
		case WALSNDSTATE_STREAMING:
			return "streaming";
		case WALSNDSTATE_STOPPING:
			return "stopping";
	}
	return "UNKNOWN";
}