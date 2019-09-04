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
typedef  int /*<<< orphan*/  grant_ref_t ;
typedef  int /*<<< orphan*/  domid_t ;
struct TYPE_2__ {int /*<<< orphan*/  (* update_entry ) (int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned long,int) ;} ;

/* Variables and functions */
 int GTF_permit_access ; 
 int GTF_readonly ; 
 TYPE_1__* gnttab_interface ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned long,int) ; 

void gnttab_grant_foreign_access_ref(grant_ref_t ref, domid_t domid,
				     unsigned long frame, int readonly)
{
	gnttab_interface->update_entry(ref, domid, frame,
			   GTF_permit_access | (readonly ? GTF_readonly : 0));
}