#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_9__ {scalar_t__ loopback; int /*<<< orphan*/  clock_type; int /*<<< orphan*/  clock_rate; } ;
typedef  TYPE_3__ sync_serial_settings ;
typedef  int /*<<< orphan*/  sync ;
struct TYPE_7__ {int /*<<< orphan*/  sync; } ;
struct TYPE_8__ {int size; TYPE_1__ ifs_ifsu; int /*<<< orphan*/  type; } ;
struct ifreq {TYPE_2__ ifr_settings; } ;
struct fst_port_info {int hwif; int index; } ;
struct fst_card_info {int dummy; } ;
struct TYPE_10__ {int /*<<< orphan*/  internalClock; int /*<<< orphan*/  lineSpeed; } ;

/* Variables and functions */
 int /*<<< orphan*/  CLOCK_EXT ; 
 int /*<<< orphan*/  CLOCK_INT ; 
#define  E1 133 
 int EFAULT ; 
 int ENOMEM ; 
 scalar_t__ FST_RDB (struct fst_card_info*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  FST_RDL (struct fst_card_info*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  IF_IFACE_E1 ; 
 int /*<<< orphan*/  IF_IFACE_T1 ; 
 int /*<<< orphan*/  IF_IFACE_V24 ; 
 int /*<<< orphan*/  IF_IFACE_V35 ; 
 int /*<<< orphan*/  IF_IFACE_X21 ; 
 int /*<<< orphan*/  IF_IFACE_X21D ; 
 scalar_t__ INTCLK ; 
#define  T1 132 
#define  V24 131 
#define  V35 130 
#define  X21 129 
#define  X21D 128 
 scalar_t__ copy_to_user (int /*<<< orphan*/ ,TYPE_3__*,int) ; 
 int /*<<< orphan*/  memset (TYPE_3__*,int /*<<< orphan*/ ,int) ; 
 TYPE_4__* portConfig ; 

__attribute__((used)) static int
fst_get_iface(struct fst_card_info *card, struct fst_port_info *port,
	      struct ifreq *ifr)
{
	sync_serial_settings sync;
	int i;

	/* First check what line type is set, we'll default to reporting X.21
	 * if nothing is set as IF_IFACE_SYNC_SERIAL implies it can't be
	 * changed
	 */
	switch (port->hwif) {
	case E1:
		ifr->ifr_settings.type = IF_IFACE_E1;
		break;
	case T1:
		ifr->ifr_settings.type = IF_IFACE_T1;
		break;
	case V35:
		ifr->ifr_settings.type = IF_IFACE_V35;
		break;
	case V24:
		ifr->ifr_settings.type = IF_IFACE_V24;
		break;
	case X21D:
		ifr->ifr_settings.type = IF_IFACE_X21D;
		break;
	case X21:
	default:
		ifr->ifr_settings.type = IF_IFACE_X21;
		break;
	}
	if (ifr->ifr_settings.size == 0) {
		return 0;	/* only type requested */
	}
	if (ifr->ifr_settings.size < sizeof (sync)) {
		return -ENOMEM;
	}

	i = port->index;
	memset(&sync, 0, sizeof(sync));
	sync.clock_rate = FST_RDL(card, portConfig[i].lineSpeed);
	/* Lucky card and linux use same encoding here */
	sync.clock_type = FST_RDB(card, portConfig[i].internalClock) ==
	    INTCLK ? CLOCK_INT : CLOCK_EXT;
	sync.loopback = 0;

	if (copy_to_user(ifr->ifr_settings.ifs_ifsu.sync, &sync, sizeof (sync))) {
		return -EFAULT;
	}

	ifr->ifr_settings.size = sizeof (sync);
	return 0;
}