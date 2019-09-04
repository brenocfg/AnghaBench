#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {int vendor_id; int subsystem_id; } ;
struct hda_codec {TYPE_1__ core; } ;

/* Variables and functions */

__attribute__((used)) static bool hp_bnb2011_with_dock(struct hda_codec *codec)
{
	if (codec->core.vendor_id != 0x111d7605 &&
	    codec->core.vendor_id != 0x111d76d1)
		return false;

	switch (codec->core.subsystem_id) {
	case 0x103c1618:
	case 0x103c1619:
	case 0x103c161a:
	case 0x103c161b:
	case 0x103c161c:
	case 0x103c161d:
	case 0x103c161e:
	case 0x103c161f:

	case 0x103c162a:
	case 0x103c162b:

	case 0x103c1630:
	case 0x103c1631:

	case 0x103c1633:
	case 0x103c1634:
	case 0x103c1635:

	case 0x103c3587:
	case 0x103c3588:
	case 0x103c3589:
	case 0x103c358a:

	case 0x103c3667:
	case 0x103c3668:
	case 0x103c3669:

		return true;
	}
	return false;
}