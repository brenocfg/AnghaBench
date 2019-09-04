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
struct snd_info_entry {struct rme96* private_data; } ;
struct snd_info_buffer {int dummy; } ;
struct rme96 {int wcreg; int areg; scalar_t__* vol; TYPE_1__* card; scalar_t__ iobase; int /*<<< orphan*/  rcreg; } ;
struct TYPE_2__ {scalar_t__ number; int /*<<< orphan*/  longname; } ;

/* Variables and functions */
 int RME96_AR_WSEL ; 
#define  RME96_ATTENUATION_0 140 
#define  RME96_ATTENUATION_12 139 
#define  RME96_ATTENUATION_18 138 
#define  RME96_ATTENUATION_6 137 
 scalar_t__ RME96_HAS_ANALOG_IN (struct rme96*) ; 
#define  RME96_INPUT_ANALOG 136 
#define  RME96_INPUT_COAXIAL 135 
#define  RME96_INPUT_INTERNAL 134 
#define  RME96_INPUT_OPTICAL 133 
#define  RME96_INPUT_XLR 132 
 scalar_t__ RME96_IO_CONTROL_REGISTER ; 
#define  RME96_MONITOR_TRACKS_1_2 131 
#define  RME96_MONITOR_TRACKS_3_4 130 
#define  RME96_MONITOR_TRACKS_5_6 129 
#define  RME96_MONITOR_TRACKS_7_8 128 
 int RME96_WCR_DOLBY ; 
 int RME96_WCR_EMP ; 
 int RME96_WCR_IDIS ; 
 int RME96_WCR_ISEL ; 
 int RME96_WCR_MASTER ; 
 int RME96_WCR_MODE24 ; 
 int RME96_WCR_MODE24_2 ; 
 int RME96_WCR_PRO ; 
 int RME96_WCR_SEL ; 
 int /*<<< orphan*/  readl (scalar_t__) ; 
 int /*<<< orphan*/  snd_iprintf (struct snd_info_buffer*,char*,...) ; 
 scalar_t__ snd_rme96_capture_getrate (struct rme96*,int*) ; 
 int snd_rme96_getattenuation (struct rme96*) ; 
 int const snd_rme96_getinputtype (struct rme96*) ; 
 int snd_rme96_getmontracks (struct rme96*) ; 
 scalar_t__ snd_rme96_playback_getrate (struct rme96*) ; 

__attribute__((used)) static void 
snd_rme96_proc_read(struct snd_info_entry *entry, struct snd_info_buffer *buffer)
{
	int n;
	struct rme96 *rme96 = entry->private_data;
	
	rme96->rcreg = readl(rme96->iobase + RME96_IO_CONTROL_REGISTER);

	snd_iprintf(buffer, rme96->card->longname);
	snd_iprintf(buffer, " (index #%d)\n", rme96->card->number + 1);

	snd_iprintf(buffer, "\nGeneral settings\n");
	if (rme96->wcreg & RME96_WCR_IDIS) {
		snd_iprintf(buffer, "  period size: N/A (interrupts "
			    "disabled)\n");
	} else if (rme96->wcreg & RME96_WCR_ISEL) {
		snd_iprintf(buffer, "  period size: 2048 bytes\n");
	} else {
		snd_iprintf(buffer, "  period size: 8192 bytes\n");
	}	
	snd_iprintf(buffer, "\nInput settings\n");
	switch (snd_rme96_getinputtype(rme96)) {
	case RME96_INPUT_OPTICAL:
		snd_iprintf(buffer, "  input: optical");
		break;
	case RME96_INPUT_COAXIAL:
		snd_iprintf(buffer, "  input: coaxial");
		break;
	case RME96_INPUT_INTERNAL:
		snd_iprintf(buffer, "  input: internal");
		break;
	case RME96_INPUT_XLR:
		snd_iprintf(buffer, "  input: XLR");
		break;
	case RME96_INPUT_ANALOG:
		snd_iprintf(buffer, "  input: analog");
		break;
	}
	if (snd_rme96_capture_getrate(rme96, &n) < 0) {
		snd_iprintf(buffer, "\n  sample rate: no valid signal\n");
	} else {
		if (n) {
			snd_iprintf(buffer, " (8 channels)\n");
		} else {
			snd_iprintf(buffer, " (2 channels)\n");
		}
		snd_iprintf(buffer, "  sample rate: %d Hz\n",
			    snd_rme96_capture_getrate(rme96, &n));
	}
	if (rme96->wcreg & RME96_WCR_MODE24_2) {
		snd_iprintf(buffer, "  sample format: 24 bit\n");
	} else {
		snd_iprintf(buffer, "  sample format: 16 bit\n");
	}
	
	snd_iprintf(buffer, "\nOutput settings\n");
	if (rme96->wcreg & RME96_WCR_SEL) {
		snd_iprintf(buffer, "  output signal: normal playback\n");
	} else {
		snd_iprintf(buffer, "  output signal: same as input\n");
	}
	snd_iprintf(buffer, "  sample rate: %d Hz\n",
		    snd_rme96_playback_getrate(rme96));
	if (rme96->wcreg & RME96_WCR_MODE24) {
		snd_iprintf(buffer, "  sample format: 24 bit\n");
	} else {
		snd_iprintf(buffer, "  sample format: 16 bit\n");
	}
	if (rme96->areg & RME96_AR_WSEL) {
		snd_iprintf(buffer, "  sample clock source: word clock\n");
	} else if (rme96->wcreg & RME96_WCR_MASTER) {
		snd_iprintf(buffer, "  sample clock source: internal\n");
	} else if (snd_rme96_getinputtype(rme96) == RME96_INPUT_ANALOG) {
		snd_iprintf(buffer, "  sample clock source: autosync (internal anyway due to analog input setting)\n");
	} else if (snd_rme96_capture_getrate(rme96, &n) < 0) {
		snd_iprintf(buffer, "  sample clock source: autosync (internal anyway due to no valid signal)\n");
	} else {
		snd_iprintf(buffer, "  sample clock source: autosync\n");
	}
	if (rme96->wcreg & RME96_WCR_PRO) {
		snd_iprintf(buffer, "  format: AES/EBU (professional)\n");
	} else {
		snd_iprintf(buffer, "  format: IEC958 (consumer)\n");
	}
	if (rme96->wcreg & RME96_WCR_EMP) {
		snd_iprintf(buffer, "  emphasis: on\n");
	} else {
		snd_iprintf(buffer, "  emphasis: off\n");
	}
	if (rme96->wcreg & RME96_WCR_DOLBY) {
		snd_iprintf(buffer, "  non-audio (dolby): on\n");
	} else {
		snd_iprintf(buffer, "  non-audio (dolby): off\n");
	}
	if (RME96_HAS_ANALOG_IN(rme96)) {
		snd_iprintf(buffer, "\nAnalog output settings\n");
		switch (snd_rme96_getmontracks(rme96)) {
		case RME96_MONITOR_TRACKS_1_2:
			snd_iprintf(buffer, "  monitored ADAT tracks: 1+2\n");
			break;
		case RME96_MONITOR_TRACKS_3_4:
			snd_iprintf(buffer, "  monitored ADAT tracks: 3+4\n");
			break;
		case RME96_MONITOR_TRACKS_5_6:
			snd_iprintf(buffer, "  monitored ADAT tracks: 5+6\n");
			break;
		case RME96_MONITOR_TRACKS_7_8:
			snd_iprintf(buffer, "  monitored ADAT tracks: 7+8\n");
			break;
		}
		switch (snd_rme96_getattenuation(rme96)) {
		case RME96_ATTENUATION_0:
			snd_iprintf(buffer, "  attenuation: 0 dB\n");
			break;
		case RME96_ATTENUATION_6:
			snd_iprintf(buffer, "  attenuation: -6 dB\n");
			break;
		case RME96_ATTENUATION_12:
			snd_iprintf(buffer, "  attenuation: -12 dB\n");
			break;
		case RME96_ATTENUATION_18:
			snd_iprintf(buffer, "  attenuation: -18 dB\n");
			break;
		}
		snd_iprintf(buffer, "  volume left: %u\n", rme96->vol[0]);
		snd_iprintf(buffer, "  volume right: %u\n", rme96->vol[1]);
	}
}