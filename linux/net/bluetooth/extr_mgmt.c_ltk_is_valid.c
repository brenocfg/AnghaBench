#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int* b; } ;
struct TYPE_4__ {int type; TYPE_1__ bdaddr; } ;
struct mgmt_ltk_info {int master; TYPE_2__ addr; } ;

/* Variables and functions */
#define  BDADDR_LE_PUBLIC 129 
#define  BDADDR_LE_RANDOM 128 

__attribute__((used)) static bool ltk_is_valid(struct mgmt_ltk_info *key)
{
	if (key->master != 0x00 && key->master != 0x01)
		return false;

	switch (key->addr.type) {
	case BDADDR_LE_PUBLIC:
		return true;

	case BDADDR_LE_RANDOM:
		/* Two most significant bits shall be set */
		if ((key->addr.bdaddr.b[5] & 0xc0) != 0xc0)
			return false;
		return true;
	}

	return false;
}