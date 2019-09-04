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
typedef  int /*<<< orphan*/  u8 ;
struct esas2r_adapter {TYPE_1__* pcid; } ;
struct TYPE_2__ {int device; } ;

/* Variables and functions */
#define  ATTO_DID_INTEL_IOP348 132 
#define  ATTO_DID_MV_88RC9580 131 
#define  ATTO_DID_MV_88RC9580TL 130 
#define  ATTO_DID_MV_88RC9580TS 129 
#define  ATTO_DID_MV_88RC9580TSE 128 
 int /*<<< orphan*/  FI_AT_MV_9580 ; 
 int /*<<< orphan*/  FI_AT_SUN_LAKE ; 
 int /*<<< orphan*/  FI_AT_UNKNWN ; 

__attribute__((used)) static u8 get_fi_adap_type(struct esas2r_adapter *a)
{
	u8 type;

	/* use the device ID to get the correct adap_typ for this HBA */
	switch (a->pcid->device) {
	case ATTO_DID_INTEL_IOP348:
		type = FI_AT_SUN_LAKE;
		break;

	case ATTO_DID_MV_88RC9580:
	case ATTO_DID_MV_88RC9580TS:
	case ATTO_DID_MV_88RC9580TSE:
	case ATTO_DID_MV_88RC9580TL:
		type = FI_AT_MV_9580;
		break;

	default:
		type = FI_AT_UNKNWN;
		break;
	}

	return type;
}