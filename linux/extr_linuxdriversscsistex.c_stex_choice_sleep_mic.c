#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct st_hba {int /*<<< orphan*/  msi_lock; } ;
struct TYPE_3__ {int event; } ;
typedef  TYPE_1__ pm_message_t ;

/* Variables and functions */
#define  PM_EVENT_HIBERNATE 129 
#define  PM_EVENT_SUSPEND 128 
 int ST_NOTHANDLED ; 
 int ST_S3 ; 
 int ST_S4 ; 

__attribute__((used)) static int stex_choice_sleep_mic(struct st_hba *hba, pm_message_t state)
{
	switch (state.event) {
	case PM_EVENT_SUSPEND:
		return ST_S3;
	case PM_EVENT_HIBERNATE:
		hba->msi_lock = 0;
		return ST_S4;
	default:
		return ST_NOTHANDLED;
	}
}