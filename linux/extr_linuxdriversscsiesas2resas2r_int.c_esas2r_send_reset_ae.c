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
typedef  union atto_vda_ae {int dummy; } atto_vda_ae ;
typedef  scalar_t__ u8 ;
struct esas2r_adapter {int dummy; } ;
struct atto_vda_ae_hdr {scalar_t__ bylength; scalar_t__ byflags; int /*<<< orphan*/  byversion; int /*<<< orphan*/  bytype; } ;

/* Variables and functions */
 int /*<<< orphan*/  VDAAE_HDR_TYPE_PWRMGT ; 
 int /*<<< orphan*/  VDAAE_HDR_TYPE_RESET ; 
 int /*<<< orphan*/  VDAAE_HDR_VER_0 ; 
 int /*<<< orphan*/  esas2r_hdebug (char*) ; 
 int /*<<< orphan*/  esas2r_queue_fw_event (struct esas2r_adapter*,int /*<<< orphan*/ ,struct atto_vda_ae_hdr*,int) ; 
 int /*<<< orphan*/  fw_event_vda_ae ; 

void esas2r_send_reset_ae(struct esas2r_adapter *a, bool pwr_mgt)
{
	struct atto_vda_ae_hdr ae;

	if (pwr_mgt)
		ae.bytype = VDAAE_HDR_TYPE_PWRMGT;
	else
		ae.bytype = VDAAE_HDR_TYPE_RESET;

	ae.byversion = VDAAE_HDR_VER_0;
	ae.byflags = 0;
	ae.bylength = (u8)sizeof(struct atto_vda_ae_hdr);

	if (pwr_mgt)
		esas2r_hdebug("*** sending power management AE ***");
	else
		esas2r_hdebug("*** sending reset AE ***");

	esas2r_queue_fw_event(a, fw_event_vda_ae, &ae,
			      sizeof(union atto_vda_ae));
}