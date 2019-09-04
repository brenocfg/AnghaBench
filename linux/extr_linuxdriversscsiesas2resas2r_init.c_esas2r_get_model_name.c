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
struct esas2r_adapter {TYPE_1__* pcid; } ;
struct TYPE_2__ {int subsystem_device; } ;

/* Variables and functions */
#define  ATTO_ESAS_R608 136 
#define  ATTO_ESAS_R60F 135 
#define  ATTO_ESAS_R644 134 
#define  ATTO_ESAS_R648 133 
#define  ATTO_ESAS_R680 132 
#define  ATTO_ESAS_R6F0 131 
#define  ATTO_TLSH_1068 130 
#define  ATTO_TSSC_3808 129 
#define  ATTO_TSSC_3808E 128 

const char *esas2r_get_model_name(struct esas2r_adapter *a)
{
	switch (a->pcid->subsystem_device) {
	case ATTO_ESAS_R680:
		return "ATTO ExpressSAS R680";

	case ATTO_ESAS_R608:
		return "ATTO ExpressSAS R608";

	case ATTO_ESAS_R60F:
		return "ATTO ExpressSAS R60F";

	case ATTO_ESAS_R6F0:
		return "ATTO ExpressSAS R6F0";

	case ATTO_ESAS_R644:
		return "ATTO ExpressSAS R644";

	case ATTO_ESAS_R648:
		return "ATTO ExpressSAS R648";

	case ATTO_TSSC_3808:
		return "ATTO ThunderStream SC 3808D";

	case ATTO_TSSC_3808E:
		return "ATTO ThunderStream SC 3808E";

	case ATTO_TLSH_1068:
		return "ATTO ThunderLink SH 1068";
	}

	return "ATTO SAS Controller";
}