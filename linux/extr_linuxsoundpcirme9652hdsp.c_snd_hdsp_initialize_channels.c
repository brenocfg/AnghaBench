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
struct hdsp {int io_type; char* card_name; void* ds_out_channels; void* ds_in_channels; void* ss_out_channels; void* ss_in_channels; int /*<<< orphan*/  qs_out_channels; int /*<<< orphan*/  qs_in_channels; } ;

/* Variables and functions */
 void* DIGIFACE_DS_CHANNELS ; 
 void* DIGIFACE_SS_CHANNELS ; 
#define  Digiface 132 
#define  H9632 131 
 int /*<<< orphan*/  H9632_DS_CHANNELS ; 
 int /*<<< orphan*/  H9632_QS_CHANNELS ; 
 int /*<<< orphan*/  H9632_SS_CHANNELS ; 
#define  H9652 130 
 void* H9652_DS_CHANNELS ; 
 void* H9652_SS_CHANNELS ; 
 int HDSP_AEBI ; 
 int HDSP_AEBO ; 
 int /*<<< orphan*/  HDSP_statusRegister ; 
 void* MULTIFACE_DS_CHANNELS ; 
 void* MULTIFACE_SS_CHANNELS ; 
#define  Multiface 129 
#define  RPM 128 
 void* RPM_CHANNELS ; 
 int hdsp_read (struct hdsp*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void snd_hdsp_initialize_channels(struct hdsp *hdsp)
{
	int status, aebi_channels, aebo_channels;

	switch (hdsp->io_type) {
	case Digiface:
		hdsp->card_name = "RME Hammerfall DSP + Digiface";
		hdsp->ss_in_channels = hdsp->ss_out_channels = DIGIFACE_SS_CHANNELS;
		hdsp->ds_in_channels = hdsp->ds_out_channels = DIGIFACE_DS_CHANNELS;
		break;

	case H9652:
		hdsp->card_name = "RME Hammerfall HDSP 9652";
		hdsp->ss_in_channels = hdsp->ss_out_channels = H9652_SS_CHANNELS;
		hdsp->ds_in_channels = hdsp->ds_out_channels = H9652_DS_CHANNELS;
		break;

	case H9632:
		status = hdsp_read(hdsp, HDSP_statusRegister);
		/* HDSP_AEBx bits are low when AEB are connected */
		aebi_channels = (status & HDSP_AEBI) ? 0 : 4;
		aebo_channels = (status & HDSP_AEBO) ? 0 : 4;
		hdsp->card_name = "RME Hammerfall HDSP 9632";
		hdsp->ss_in_channels = H9632_SS_CHANNELS+aebi_channels;
		hdsp->ds_in_channels = H9632_DS_CHANNELS+aebi_channels;
		hdsp->qs_in_channels = H9632_QS_CHANNELS+aebi_channels;
		hdsp->ss_out_channels = H9632_SS_CHANNELS+aebo_channels;
		hdsp->ds_out_channels = H9632_DS_CHANNELS+aebo_channels;
		hdsp->qs_out_channels = H9632_QS_CHANNELS+aebo_channels;
		break;

	case Multiface:
		hdsp->card_name = "RME Hammerfall DSP + Multiface";
		hdsp->ss_in_channels = hdsp->ss_out_channels = MULTIFACE_SS_CHANNELS;
		hdsp->ds_in_channels = hdsp->ds_out_channels = MULTIFACE_DS_CHANNELS;
		break;

	case RPM:
		hdsp->card_name = "RME Hammerfall DSP + RPM";
		hdsp->ss_in_channels = RPM_CHANNELS-1;
		hdsp->ss_out_channels = RPM_CHANNELS;
		hdsp->ds_in_channels = RPM_CHANNELS-1;
		hdsp->ds_out_channels = RPM_CHANNELS;
		break;

	default:
 		/* should never get here */
		break;
	}
}