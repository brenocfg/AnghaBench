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
typedef  enum CT_AMIXER_CTL { ____Placeholder_CT_AMIXER_CTL } CT_AMIXER_CTL ;

/* Variables and functions */
#define  AMIXER_LINEIN 132 
 int AMIXER_LINEIN_C ; 
#define  AMIXER_MASTER_F 131 
 int AMIXER_MASTER_F_C ; 
#define  AMIXER_MIC 130 
 int AMIXER_MIC_C ; 
#define  AMIXER_PCM_F 129 
 int AMIXER_PCM_F_C ; 
#define  AMIXER_SPDIFI 128 
 int AMIXER_SPDIFI_C ; 
 int NUM_CT_AMIXERS ; 

__attribute__((used)) static enum CT_AMIXER_CTL get_recording_amixer(enum CT_AMIXER_CTL index)
{
	switch (index) {
	case AMIXER_MASTER_F:	return AMIXER_MASTER_F_C;
	case AMIXER_PCM_F:	return AMIXER_PCM_F_C;
	case AMIXER_SPDIFI:	return AMIXER_SPDIFI_C;
	case AMIXER_LINEIN:	return AMIXER_LINEIN_C;
	case AMIXER_MIC:	return AMIXER_MIC_C;
	default:		return NUM_CT_AMIXERS;
	}
}