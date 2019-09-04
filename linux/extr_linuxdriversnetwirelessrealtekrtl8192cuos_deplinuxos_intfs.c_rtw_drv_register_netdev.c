#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct dvobj_priv {int iface_nums; TYPE_2__** padapters; } ;
struct TYPE_5__ {char* ifname; char* if2name; } ;
struct TYPE_6__ {scalar_t__ iface_id; TYPE_1__ registrypriv; struct dvobj_priv* dvobj; } ;
typedef  TYPE_2__ _adapter ;

/* Variables and functions */
 scalar_t__ IFACE_ID0 ; 
 scalar_t__ IFACE_ID1 ; 
 int IFACE_ID_MAX ; 
 int _SUCCESS ; 
 int _rtw_drv_register_netdev (TYPE_2__*,char*) ; 

int rtw_drv_register_netdev(_adapter *if1)
{
	int i, status = _SUCCESS;
	struct dvobj_priv *dvobj = if1->dvobj;

	if(dvobj->iface_nums < IFACE_ID_MAX)
	{
		for(i=0; i<dvobj->iface_nums; i++)
		{
			_adapter *padapter = dvobj->padapters[i];

			if(padapter)
			{
				char *name;

				if(padapter->iface_id == IFACE_ID0)
					name = if1->registrypriv.ifname;
				else if(padapter->iface_id == IFACE_ID1)
					name = if1->registrypriv.if2name;
				else
					name = "wlan%d";

				if((status = _rtw_drv_register_netdev(padapter, name)) != _SUCCESS) {
					break;
				}
			}
		}
	}

	return status;
}