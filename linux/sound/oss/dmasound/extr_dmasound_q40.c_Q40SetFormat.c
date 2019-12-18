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
struct TYPE_5__ {int format; int size; } ;
struct TYPE_4__ {int format; int size; } ;
struct TYPE_6__ {scalar_t__ minDev; TYPE_2__ dsp; TYPE_1__ soft; } ;

/* Variables and functions */
#define  AFMT_A_LAW 132 
#define  AFMT_MU_LAW 131 
#define  AFMT_QUERY 130 
#define  AFMT_S8 129 
#define  AFMT_U8 128 
 int /*<<< orphan*/  Q40Init () ; 
 scalar_t__ SND_DEV_DSP ; 
 TYPE_3__ dmasound ; 

__attribute__((used)) static int Q40SetFormat(int format)
{
	/* Q40 sound supports only 8bit modes */

	switch (format) {
	case AFMT_QUERY:
		return(dmasound.soft.format);
	case AFMT_MU_LAW:
	case AFMT_A_LAW:
	case AFMT_S8:
	case AFMT_U8:
		break;
	default:
		format = AFMT_S8;
	}

	dmasound.soft.format = format;
	dmasound.soft.size = 8;
	if (dmasound.minDev == SND_DEV_DSP) {
		dmasound.dsp.format = format;
		dmasound.dsp.size = 8;
	}
	Q40Init();

	return(format);
}