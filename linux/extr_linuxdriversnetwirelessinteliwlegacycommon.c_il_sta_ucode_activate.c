#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  size_t u8 ;
struct il_priv {TYPE_3__* stations; } ;
struct TYPE_4__ {int /*<<< orphan*/  addr; } ;
struct TYPE_5__ {TYPE_1__ sta; } ;
struct TYPE_6__ {int used; TYPE_2__ sta; } ;

/* Variables and functions */
 int /*<<< orphan*/  D_ASSOC (char*,size_t,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  IL_ERR (char*,size_t,int /*<<< orphan*/ ) ; 
 int IL_STA_DRIVER_ACTIVE ; 
 int IL_STA_UCODE_ACTIVE ; 

__attribute__((used)) static void
il_sta_ucode_activate(struct il_priv *il, u8 sta_id)
{

	if (!(il->stations[sta_id].used & IL_STA_DRIVER_ACTIVE))
		IL_ERR("ACTIVATE a non DRIVER active station id %u addr %pM\n",
		       sta_id, il->stations[sta_id].sta.sta.addr);

	if (il->stations[sta_id].used & IL_STA_UCODE_ACTIVE) {
		D_ASSOC("STA id %u addr %pM already present"
			" in uCode (according to driver)\n", sta_id,
			il->stations[sta_id].sta.sta.addr);
	} else {
		il->stations[sta_id].used |= IL_STA_UCODE_ACTIVE;
		D_ASSOC("Added STA id %u addr %pM to uCode\n", sta_id,
			il->stations[sta_id].sta.sta.addr);
	}
}