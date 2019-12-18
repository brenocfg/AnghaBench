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
struct hdsp {scalar_t__ io_type; } ;

/* Variables and functions */
 scalar_t__ H9632 ; 
 scalar_t__ HDSP_AUTOSYNC_FROM_SPDIF ; 
 int /*<<< orphan*/  HDSP_status2Register ; 
#define  HDSP_systemFrequency32 133 
#define  HDSP_systemFrequency44_1 132 
#define  HDSP_systemFrequency48 131 
#define  HDSP_systemFrequency64 130 
#define  HDSP_systemFrequency88_2 129 
#define  HDSP_systemFrequency96 128 
 unsigned int HDSP_systemFrequencyMask ; 
 scalar_t__ hdsp_autosync_ref (struct hdsp*) ; 
 unsigned int hdsp_read (struct hdsp*,int /*<<< orphan*/ ) ; 
 int hdsp_spdif_sample_rate (struct hdsp*) ; 

__attribute__((used)) static int hdsp_external_sample_rate(struct hdsp *hdsp)
{
	unsigned int status2 = hdsp_read(hdsp, HDSP_status2Register);
	unsigned int rate_bits = status2 & HDSP_systemFrequencyMask;

	/* For the 9632 card, there seems to be no bit for indicating external
	 * sample rate greater than 96kHz. The card reports the corresponding
	 * single speed. So the best means seems to get spdif rate when
	 * autosync reference is spdif */
	if (hdsp->io_type == H9632 &&
	    hdsp_autosync_ref(hdsp) == HDSP_AUTOSYNC_FROM_SPDIF)
		 return hdsp_spdif_sample_rate(hdsp);

	switch (rate_bits) {
	case HDSP_systemFrequency32:   return 32000;
	case HDSP_systemFrequency44_1: return 44100;
	case HDSP_systemFrequency48:   return 48000;
	case HDSP_systemFrequency64:   return 64000;
	case HDSP_systemFrequency88_2: return 88200;
	case HDSP_systemFrequency96:   return 96000;
	default:
		return 0;
	}
}