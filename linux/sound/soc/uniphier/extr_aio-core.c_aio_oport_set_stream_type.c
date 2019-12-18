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
typedef  int u32 ;
struct uniphier_aio_sub {TYPE_4__* swm; TYPE_2__* aio; } ;
struct regmap {int dummy; } ;
typedef  enum IEC61937_PC { ____Placeholder_IEC61937_PC } IEC61937_PC ;
struct TYPE_7__ {int /*<<< orphan*/  map; } ;
struct TYPE_8__ {TYPE_3__ oport; } ;
struct TYPE_6__ {TYPE_1__* chip; } ;
struct TYPE_5__ {struct regmap* regmap; } ;

/* Variables and functions */
#define  IEC61937_PC_AAC 135 
#define  IEC61937_PC_AC3 134 
#define  IEC61937_PC_DTS1 133 
#define  IEC61937_PC_DTS2 132 
#define  IEC61937_PC_DTS3 131 
#define  IEC61937_PC_MP3 130 
#define  IEC61937_PC_MPA 129 
#define  IEC61937_PC_PAUSE 128 
 int /*<<< orphan*/  OPORTMXPAUDAT (int /*<<< orphan*/ ) ; 
 int OPORTMXPAUDAT_PAUSEPC_CMN ; 
 int OPORTMXPAUDAT_PAUSEPD_AAC ; 
 int OPORTMXPAUDAT_PAUSEPD_AC3 ; 
 int OPORTMXPAUDAT_PAUSEPD_DTS1 ; 
 int OPORTMXPAUDAT_PAUSEPD_DTS2 ; 
 int OPORTMXPAUDAT_PAUSEPD_DTS3 ; 
 int OPORTMXPAUDAT_PAUSEPD_MP3 ; 
 int OPORTMXPAUDAT_PAUSEPD_MPA ; 
 int /*<<< orphan*/  OPORTMXREPET (int /*<<< orphan*/ ) ; 
 int OPORTMXREPET_PMLENGTH_AAC ; 
 int OPORTMXREPET_PMLENGTH_AC3 ; 
 int OPORTMXREPET_PMLENGTH_DTS1 ; 
 int OPORTMXREPET_PMLENGTH_DTS2 ; 
 int OPORTMXREPET_PMLENGTH_DTS3 ; 
 int OPORTMXREPET_PMLENGTH_MP3 ; 
 int OPORTMXREPET_PMLENGTH_MPA ; 
 int OPORTMXREPET_STRLENGTH_AAC ; 
 int OPORTMXREPET_STRLENGTH_AC3 ; 
 int OPORTMXREPET_STRLENGTH_DTS1 ; 
 int OPORTMXREPET_STRLENGTH_DTS2 ; 
 int OPORTMXREPET_STRLENGTH_DTS3 ; 
 int OPORTMXREPET_STRLENGTH_MP3 ; 
 int OPORTMXREPET_STRLENGTH_MPA ; 
 int /*<<< orphan*/  regmap_write (struct regmap*,int /*<<< orphan*/ ,int) ; 

int aio_oport_set_stream_type(struct uniphier_aio_sub *sub,
			      enum IEC61937_PC pc)
{
	struct regmap *r = sub->aio->chip->regmap;
	u32 repet = 0, pause = OPORTMXPAUDAT_PAUSEPC_CMN;

	switch (pc) {
	case IEC61937_PC_AC3:
		repet = OPORTMXREPET_STRLENGTH_AC3 |
			OPORTMXREPET_PMLENGTH_AC3;
		pause |= OPORTMXPAUDAT_PAUSEPD_AC3;
		break;
	case IEC61937_PC_MPA:
		repet = OPORTMXREPET_STRLENGTH_MPA |
			OPORTMXREPET_PMLENGTH_MPA;
		pause |= OPORTMXPAUDAT_PAUSEPD_MPA;
		break;
	case IEC61937_PC_MP3:
		repet = OPORTMXREPET_STRLENGTH_MP3 |
			OPORTMXREPET_PMLENGTH_MP3;
		pause |= OPORTMXPAUDAT_PAUSEPD_MP3;
		break;
	case IEC61937_PC_DTS1:
		repet = OPORTMXREPET_STRLENGTH_DTS1 |
			OPORTMXREPET_PMLENGTH_DTS1;
		pause |= OPORTMXPAUDAT_PAUSEPD_DTS1;
		break;
	case IEC61937_PC_DTS2:
		repet = OPORTMXREPET_STRLENGTH_DTS2 |
			OPORTMXREPET_PMLENGTH_DTS2;
		pause |= OPORTMXPAUDAT_PAUSEPD_DTS2;
		break;
	case IEC61937_PC_DTS3:
		repet = OPORTMXREPET_STRLENGTH_DTS3 |
			OPORTMXREPET_PMLENGTH_DTS3;
		pause |= OPORTMXPAUDAT_PAUSEPD_DTS3;
		break;
	case IEC61937_PC_AAC:
		repet = OPORTMXREPET_STRLENGTH_AAC |
			OPORTMXREPET_PMLENGTH_AAC;
		pause |= OPORTMXPAUDAT_PAUSEPD_AAC;
		break;
	case IEC61937_PC_PAUSE:
		/* Do nothing */
		break;
	}

	regmap_write(r, OPORTMXREPET(sub->swm->oport.map), repet);
	regmap_write(r, OPORTMXPAUDAT(sub->swm->oport.map), pause);

	return 0;
}