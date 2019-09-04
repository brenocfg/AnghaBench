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
struct init_sccb {int dummy; } ;

/* Variables and functions */
 int EVTYP_VT220MSG_MASK ; 
 int sccb_get_sclp_send_mask (struct init_sccb*) ; 

unsigned int sclp_early_con_check_vt220(struct init_sccb *sccb)
{
	if (sccb_get_sclp_send_mask(sccb) & EVTYP_VT220MSG_MASK)
		return 1;
	return 0;
}