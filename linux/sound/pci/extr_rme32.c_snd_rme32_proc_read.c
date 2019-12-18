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
struct snd_info_entry {scalar_t__ private_data; } ;
struct snd_info_buffer {int dummy; } ;
struct rme32 {int rcreg; int wcreg; scalar_t__ fullduplex_mode; TYPE_1__* card; scalar_t__ iobase; } ;
struct TYPE_2__ {char* longname; scalar_t__ number; } ;

/* Variables and functions */
#define  RME32_INPUT_COAXIAL 131 
#define  RME32_INPUT_INTERNAL 130 
#define  RME32_INPUT_OPTICAL 129 
#define  RME32_INPUT_XLR 128 
 scalar_t__ RME32_IO_CONTROL_REGISTER ; 
 scalar_t__ RME32_PRO_WITH_8414 (struct rme32*) ; 
 int RME32_RCR_KMODE ; 
 int RME32_WCR_EMP ; 
 int RME32_WCR_FREQ_0 ; 
 int RME32_WCR_FREQ_1 ; 
 int RME32_WCR_MODE24 ; 
 int RME32_WCR_MONO ; 
 int RME32_WCR_MUTE ; 
 int RME32_WCR_PRO ; 
 int RME32_WCR_SEL ; 
 int readl (scalar_t__) ; 
 int /*<<< orphan*/  snd_iprintf (struct snd_info_buffer*,char*,...) ; 
 scalar_t__ snd_rme32_capture_getrate (struct rme32*,int*) ; 
 int snd_rme32_getinputtype (struct rme32*) ; 
 int /*<<< orphan*/  snd_rme32_playback_getrate (struct rme32*) ; 

__attribute__((used)) static void
snd_rme32_proc_read(struct snd_info_entry * entry, struct snd_info_buffer *buffer)
{
	int n;
	struct rme32 *rme32 = (struct rme32 *) entry->private_data;

	rme32->rcreg = readl(rme32->iobase + RME32_IO_CONTROL_REGISTER);

	snd_iprintf(buffer, rme32->card->longname);
	snd_iprintf(buffer, " (index #%d)\n", rme32->card->number + 1);

	snd_iprintf(buffer, "\nGeneral settings\n");
	if (rme32->fullduplex_mode)
		snd_iprintf(buffer, "  Full-duplex mode\n");
	else
		snd_iprintf(buffer, "  Half-duplex mode\n");
	if (RME32_PRO_WITH_8414(rme32)) {
		snd_iprintf(buffer, "  receiver: CS8414\n");
	} else {
		snd_iprintf(buffer, "  receiver: CS8412\n");
	}
	if (rme32->wcreg & RME32_WCR_MODE24) {
		snd_iprintf(buffer, "  format: 24 bit");
	} else {
		snd_iprintf(buffer, "  format: 16 bit");
	}
	if (rme32->wcreg & RME32_WCR_MONO) {
		snd_iprintf(buffer, ", Mono\n");
	} else {
		snd_iprintf(buffer, ", Stereo\n");
	}

	snd_iprintf(buffer, "\nInput settings\n");
	switch (snd_rme32_getinputtype(rme32)) {
	case RME32_INPUT_OPTICAL:
		snd_iprintf(buffer, "  input: optical");
		break;
	case RME32_INPUT_COAXIAL:
		snd_iprintf(buffer, "  input: coaxial");
		break;
	case RME32_INPUT_INTERNAL:
		snd_iprintf(buffer, "  input: internal");
		break;
	case RME32_INPUT_XLR:
		snd_iprintf(buffer, "  input: XLR");
		break;
	}
	if (snd_rme32_capture_getrate(rme32, &n) < 0) {
		snd_iprintf(buffer, "\n  sample rate: no valid signal\n");
	} else {
		if (n) {
			snd_iprintf(buffer, " (8 channels)\n");
		} else {
			snd_iprintf(buffer, " (2 channels)\n");
		}
		snd_iprintf(buffer, "  sample rate: %d Hz\n",
			    snd_rme32_capture_getrate(rme32, &n));
	}

	snd_iprintf(buffer, "\nOutput settings\n");
	if (rme32->wcreg & RME32_WCR_SEL) {
		snd_iprintf(buffer, "  output signal: normal playback");
	} else {
		snd_iprintf(buffer, "  output signal: same as input");
	}
	if (rme32->wcreg & RME32_WCR_MUTE) {
		snd_iprintf(buffer, " (muted)\n");
	} else {
		snd_iprintf(buffer, "\n");
	}

	/* master output frequency */
	if (!
	    ((!(rme32->wcreg & RME32_WCR_FREQ_0))
	     && (!(rme32->wcreg & RME32_WCR_FREQ_1)))) {
		snd_iprintf(buffer, "  sample rate: %d Hz\n",
			    snd_rme32_playback_getrate(rme32));
	}
	if (rme32->rcreg & RME32_RCR_KMODE) {
		snd_iprintf(buffer, "  sample clock source: AutoSync\n");
	} else {
		snd_iprintf(buffer, "  sample clock source: Internal\n");
	}
	if (rme32->wcreg & RME32_WCR_PRO) {
		snd_iprintf(buffer, "  format: AES/EBU (professional)\n");
	} else {
		snd_iprintf(buffer, "  format: IEC958 (consumer)\n");
	}
	if (rme32->wcreg & RME32_WCR_EMP) {
		snd_iprintf(buffer, "  emphasis: on\n");
	} else {
		snd_iprintf(buffer, "  emphasis: off\n");
	}
}