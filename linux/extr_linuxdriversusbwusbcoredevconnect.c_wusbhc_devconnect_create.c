#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {int bLength; int /*<<< orphan*/  bIEIdentifier; } ;
struct TYPE_8__ {TYPE_3__ hdr; } ;
struct TYPE_5__ {int bLength; int /*<<< orphan*/  bIEIdentifier; } ;
struct TYPE_6__ {TYPE_1__ hdr; } ;
struct wusbhc {int /*<<< orphan*/  cack_list; TYPE_4__ cack_ie; int /*<<< orphan*/  keep_alive_timer; TYPE_2__ keep_alive_ie; } ;

/* Variables and functions */
 int /*<<< orphan*/  INIT_DELAYED_WORK (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  INIT_LIST_HEAD (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  WUIE_ID_CONNECTACK ; 
 int /*<<< orphan*/  WUIE_ID_KEEP_ALIVE ; 
 int /*<<< orphan*/  wusbhc_keep_alive_run ; 

int wusbhc_devconnect_create(struct wusbhc *wusbhc)
{
	wusbhc->keep_alive_ie.hdr.bIEIdentifier = WUIE_ID_KEEP_ALIVE;
	wusbhc->keep_alive_ie.hdr.bLength = sizeof(wusbhc->keep_alive_ie.hdr);
	INIT_DELAYED_WORK(&wusbhc->keep_alive_timer, wusbhc_keep_alive_run);

	wusbhc->cack_ie.hdr.bIEIdentifier = WUIE_ID_CONNECTACK;
	wusbhc->cack_ie.hdr.bLength = sizeof(wusbhc->cack_ie.hdr);
	INIT_LIST_HEAD(&wusbhc->cack_list);

	return 0;
}