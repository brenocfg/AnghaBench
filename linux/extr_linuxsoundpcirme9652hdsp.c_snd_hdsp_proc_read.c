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
struct snd_info_entry {struct hdsp* private_data; } ;
struct snd_info_buffer {int dummy; } ;
struct hdsp {int control_register; int state; int io_type; scalar_t__ clock_source_locked; int /*<<< orphan*/  system_sample_rate; scalar_t__ precise_ptr; scalar_t__ period_bytes; scalar_t__ use_midi_tasklet; int /*<<< orphan*/  control2_register; scalar_t__ iobase; int /*<<< orphan*/  port; int /*<<< orphan*/  irq; int /*<<< orphan*/  playback_buffer; int /*<<< orphan*/  capture_buffer; TYPE_1__* card; int /*<<< orphan*/  card_name; } ;
struct TYPE_2__ {scalar_t__ number; } ;

/* Variables and functions */
#define  Digiface 166 
 int EINVAL ; 
 int H9632 ; 
#define  H9652 165 
#define  HDSP_AUTOSYNC_FROM_ADAT1 164 
#define  HDSP_AUTOSYNC_FROM_ADAT2 163 
#define  HDSP_AUTOSYNC_FROM_ADAT3 162 
#define  HDSP_AUTOSYNC_FROM_ADAT_SYNC 161 
#define  HDSP_AUTOSYNC_FROM_NONE 160 
#define  HDSP_AUTOSYNC_FROM_SPDIF 159 
#define  HDSP_AUTOSYNC_FROM_WORD 158 
 int HDSP_AnalogExtensionBoard ; 
#define  HDSP_CLOCK_SOURCE_AUTOSYNC 157 
#define  HDSP_CLOCK_SOURCE_INTERNAL_128KHZ 156 
#define  HDSP_CLOCK_SOURCE_INTERNAL_176_4KHZ 155 
#define  HDSP_CLOCK_SOURCE_INTERNAL_192KHZ 154 
#define  HDSP_CLOCK_SOURCE_INTERNAL_32KHZ 153 
#define  HDSP_CLOCK_SOURCE_INTERNAL_44_1KHZ 152 
#define  HDSP_CLOCK_SOURCE_INTERNAL_48KHZ 151 
#define  HDSP_CLOCK_SOURCE_INTERNAL_64KHZ 150 
#define  HDSP_CLOCK_SOURCE_INTERNAL_88_2KHZ 149 
#define  HDSP_CLOCK_SOURCE_INTERNAL_96KHZ 148 
 int HDSP_FirmwareCached ; 
 int HDSP_LatencyMask ; 
 int HDSP_LineOut ; 
 unsigned int HDSP_Lock0 ; 
 unsigned int HDSP_Lock1 ; 
 unsigned int HDSP_Lock2 ; 
 int HDSP_RPM_Bypass ; 
 int HDSP_RPM_Disconnect ; 
 int HDSP_RPM_Inp12 ; 
#define  HDSP_RPM_Inp12_Line_0dB 147 
#define  HDSP_RPM_Inp12_Line_n6dB 146 
#define  HDSP_RPM_Inp12_Phon_0dB 145 
#define  HDSP_RPM_Inp12_Phon_6dB 144 
#define  HDSP_RPM_Inp12_Phon_n6dB 143 
 int HDSP_RPM_Inp34 ; 
#define  HDSP_RPM_Inp34_Line_0dB 142 
#define  HDSP_RPM_Inp34_Line_n6dB 141 
#define  HDSP_RPM_Inp34_Phon_0dB 140 
#define  HDSP_RPM_Inp34_Phon_6dB 139 
#define  HDSP_RPM_Inp34_Phon_n6dB 138 
 int HDSP_SPDIFEmphasis ; 
 unsigned int HDSP_SPDIFErrorFlag ; 
#define  HDSP_SPDIFIN_AES 137 
#define  HDSP_SPDIFIN_COAXIAL 136 
#define  HDSP_SPDIFIN_INTERNAL 135 
#define  HDSP_SPDIFIN_OPTICAL 134 
 int HDSP_SPDIFNonAudio ; 
 int HDSP_SPDIFOpticalOut ; 
 int HDSP_SPDIFProfessional ; 
 unsigned int HDSP_SPDIFSync ; 
#define  HDSP_SYNC_FROM_ADAT1 133 
#define  HDSP_SYNC_FROM_ADAT2 132 
#define  HDSP_SYNC_FROM_ADAT3 131 
#define  HDSP_SYNC_FROM_ADAT_SYNC 130 
#define  HDSP_SYNC_FROM_SPDIF 129 
#define  HDSP_SYNC_FROM_WORD 128 
 unsigned int HDSP_Sync0 ; 
 unsigned int HDSP_Sync1 ; 
 unsigned int HDSP_Sync2 ; 
 unsigned int HDSP_TimecodeLock ; 
 unsigned int HDSP_TimecodeSync ; 
 int /*<<< orphan*/  HDSP_XLRBreakoutCable ; 
 int /*<<< orphan*/  HDSP_fifoStatus ; 
 int /*<<< orphan*/  HDSP_midiStatusIn0 ; 
 int /*<<< orphan*/  HDSP_midiStatusIn1 ; 
 int /*<<< orphan*/  HDSP_midiStatusOut0 ; 
 int /*<<< orphan*/  HDSP_midiStatusOut1 ; 
 int /*<<< orphan*/  HDSP_status2Register ; 
 int /*<<< orphan*/  HDSP_statusRegister ; 
 unsigned int HDSP_version0 ; 
 unsigned int HDSP_version1 ; 
 unsigned int HDSP_version2 ; 
 unsigned int HDSP_wc_lock ; 
 unsigned int HDSP_wc_sync ; 
 int RPM ; 
 int hdsp_ad_gain (struct hdsp*) ; 
 int hdsp_autosync_ref (struct hdsp*) ; 
 scalar_t__ hdsp_check_for_firmware (struct hdsp*,int /*<<< orphan*/ ) ; 
 scalar_t__ hdsp_check_for_iobox (struct hdsp*) ; 
 int hdsp_clock_source (struct hdsp*) ; 
 int hdsp_da_gain (struct hdsp*) ; 
 int hdsp_decode_latency (int) ; 
 int /*<<< orphan*/  hdsp_external_sample_rate (struct hdsp*) ; 
 int /*<<< orphan*/  hdsp_hw_pointer (struct hdsp*) ; 
 int hdsp_phone_gain (struct hdsp*) ; 
 int hdsp_pref_sync_ref (struct hdsp*) ; 
 int hdsp_read (struct hdsp*,int /*<<< orphan*/ ) ; 
 int hdsp_request_fw_loader (struct hdsp*) ; 
 int hdsp_spdif_in (struct hdsp*) ; 
 int hdsp_spdif_sample_rate (struct hdsp*) ; 
 scalar_t__ hdsp_system_clock_mode (struct hdsp*) ; 
 scalar_t__ hdsp_toggle_setting (struct hdsp*,int /*<<< orphan*/ ) ; 
 scalar_t__ snd_hdsp_load_firmware_from_cache (struct hdsp*) ; 
 int /*<<< orphan*/  snd_iprintf (struct snd_info_buffer*,char*,...) ; 

__attribute__((used)) static void
snd_hdsp_proc_read(struct snd_info_entry *entry, struct snd_info_buffer *buffer)
{
	struct hdsp *hdsp = entry->private_data;
	unsigned int status;
	unsigned int status2;
	char *pref_sync_ref;
	char *autosync_ref;
	char *system_clock_mode;
	char *clock_source;
	int x;

	status = hdsp_read(hdsp, HDSP_statusRegister);
	status2 = hdsp_read(hdsp, HDSP_status2Register);

	snd_iprintf(buffer, "%s (Card #%d)\n", hdsp->card_name,
		    hdsp->card->number + 1);
	snd_iprintf(buffer, "Buffers: capture %p playback %p\n",
		    hdsp->capture_buffer, hdsp->playback_buffer);
	snd_iprintf(buffer, "IRQ: %d Registers bus: 0x%lx VM: 0x%lx\n",
		    hdsp->irq, hdsp->port, (unsigned long)hdsp->iobase);
	snd_iprintf(buffer, "Control register: 0x%x\n", hdsp->control_register);
	snd_iprintf(buffer, "Control2 register: 0x%x\n",
		    hdsp->control2_register);
	snd_iprintf(buffer, "Status register: 0x%x\n", status);
	snd_iprintf(buffer, "Status2 register: 0x%x\n", status2);

	if (hdsp_check_for_iobox(hdsp)) {
		snd_iprintf(buffer, "No I/O box connected.\n"
			    "Please connect one and upload firmware.\n");
		return;
	}

	if (hdsp_check_for_firmware(hdsp, 0)) {
		if (hdsp->state & HDSP_FirmwareCached) {
			if (snd_hdsp_load_firmware_from_cache(hdsp) != 0) {
				snd_iprintf(buffer, "Firmware loading from "
					    "cache failed, "
					    "please upload manually.\n");
				return;
			}
		} else {
			int err = -EINVAL;
			err = hdsp_request_fw_loader(hdsp);
			if (err < 0) {
				snd_iprintf(buffer,
					    "No firmware loaded nor cached, "
					    "please upload firmware.\n");
				return;
			}
		}
	}

	snd_iprintf(buffer, "FIFO status: %d\n", hdsp_read(hdsp, HDSP_fifoStatus) & 0xff);
	snd_iprintf(buffer, "MIDI1 Output status: 0x%x\n", hdsp_read(hdsp, HDSP_midiStatusOut0));
	snd_iprintf(buffer, "MIDI1 Input status: 0x%x\n", hdsp_read(hdsp, HDSP_midiStatusIn0));
	snd_iprintf(buffer, "MIDI2 Output status: 0x%x\n", hdsp_read(hdsp, HDSP_midiStatusOut1));
	snd_iprintf(buffer, "MIDI2 Input status: 0x%x\n", hdsp_read(hdsp, HDSP_midiStatusIn1));
	snd_iprintf(buffer, "Use Midi Tasklet: %s\n", hdsp->use_midi_tasklet ? "on" : "off");

	snd_iprintf(buffer, "\n");

	x = 1 << (6 + hdsp_decode_latency(hdsp->control_register & HDSP_LatencyMask));

	snd_iprintf(buffer, "Buffer Size (Latency): %d samples (2 periods of %lu bytes)\n", x, (unsigned long) hdsp->period_bytes);
	snd_iprintf(buffer, "Hardware pointer (frames): %ld\n", hdsp_hw_pointer(hdsp));
	snd_iprintf(buffer, "Precise pointer: %s\n", hdsp->precise_ptr ? "on" : "off");
	snd_iprintf(buffer, "Line out: %s\n", (hdsp->control_register & HDSP_LineOut) ? "on" : "off");

	snd_iprintf(buffer, "Firmware version: %d\n", (status2&HDSP_version0)|(status2&HDSP_version1)<<1|(status2&HDSP_version2)<<2);

	snd_iprintf(buffer, "\n");

	switch (hdsp_clock_source(hdsp)) {
	case HDSP_CLOCK_SOURCE_AUTOSYNC:
		clock_source = "AutoSync";
		break;
	case HDSP_CLOCK_SOURCE_INTERNAL_32KHZ:
		clock_source = "Internal 32 kHz";
		break;
	case HDSP_CLOCK_SOURCE_INTERNAL_44_1KHZ:
		clock_source = "Internal 44.1 kHz";
		break;
	case HDSP_CLOCK_SOURCE_INTERNAL_48KHZ:
		clock_source = "Internal 48 kHz";
		break;
	case HDSP_CLOCK_SOURCE_INTERNAL_64KHZ:
		clock_source = "Internal 64 kHz";
		break;
	case HDSP_CLOCK_SOURCE_INTERNAL_88_2KHZ:
		clock_source = "Internal 88.2 kHz";
		break;
	case HDSP_CLOCK_SOURCE_INTERNAL_96KHZ:
		clock_source = "Internal 96 kHz";
		break;
	case HDSP_CLOCK_SOURCE_INTERNAL_128KHZ:
		clock_source = "Internal 128 kHz";
		break;
	case HDSP_CLOCK_SOURCE_INTERNAL_176_4KHZ:
		clock_source = "Internal 176.4 kHz";
		break;
		case HDSP_CLOCK_SOURCE_INTERNAL_192KHZ:
		clock_source = "Internal 192 kHz";
		break;
	default:
		clock_source = "Error";
	}
	snd_iprintf (buffer, "Sample Clock Source: %s\n", clock_source);

	if (hdsp_system_clock_mode(hdsp))
		system_clock_mode = "Slave";
	else
		system_clock_mode = "Master";

	switch (hdsp_pref_sync_ref (hdsp)) {
	case HDSP_SYNC_FROM_WORD:
		pref_sync_ref = "Word Clock";
		break;
	case HDSP_SYNC_FROM_ADAT_SYNC:
		pref_sync_ref = "ADAT Sync";
		break;
	case HDSP_SYNC_FROM_SPDIF:
		pref_sync_ref = "SPDIF";
		break;
	case HDSP_SYNC_FROM_ADAT1:
		pref_sync_ref = "ADAT1";
		break;
	case HDSP_SYNC_FROM_ADAT2:
		pref_sync_ref = "ADAT2";
		break;
	case HDSP_SYNC_FROM_ADAT3:
		pref_sync_ref = "ADAT3";
		break;
	default:
		pref_sync_ref = "Word Clock";
		break;
	}
	snd_iprintf (buffer, "Preferred Sync Reference: %s\n", pref_sync_ref);

	switch (hdsp_autosync_ref (hdsp)) {
	case HDSP_AUTOSYNC_FROM_WORD:
		autosync_ref = "Word Clock";
		break;
	case HDSP_AUTOSYNC_FROM_ADAT_SYNC:
		autosync_ref = "ADAT Sync";
		break;
	case HDSP_AUTOSYNC_FROM_SPDIF:
		autosync_ref = "SPDIF";
		break;
	case HDSP_AUTOSYNC_FROM_NONE:
		autosync_ref = "None";
		break;
	case HDSP_AUTOSYNC_FROM_ADAT1:
		autosync_ref = "ADAT1";
		break;
	case HDSP_AUTOSYNC_FROM_ADAT2:
		autosync_ref = "ADAT2";
		break;
	case HDSP_AUTOSYNC_FROM_ADAT3:
		autosync_ref = "ADAT3";
		break;
	default:
		autosync_ref = "---";
		break;
	}
	snd_iprintf (buffer, "AutoSync Reference: %s\n", autosync_ref);

	snd_iprintf (buffer, "AutoSync Frequency: %d\n", hdsp_external_sample_rate(hdsp));

	snd_iprintf (buffer, "System Clock Mode: %s\n", system_clock_mode);

	snd_iprintf (buffer, "System Clock Frequency: %d\n", hdsp->system_sample_rate);
	snd_iprintf (buffer, "System Clock Locked: %s\n", hdsp->clock_source_locked ? "Yes" : "No");

	snd_iprintf(buffer, "\n");

	if (hdsp->io_type != RPM) {
		switch (hdsp_spdif_in(hdsp)) {
		case HDSP_SPDIFIN_OPTICAL:
			snd_iprintf(buffer, "IEC958 input: Optical\n");
			break;
		case HDSP_SPDIFIN_COAXIAL:
			snd_iprintf(buffer, "IEC958 input: Coaxial\n");
			break;
		case HDSP_SPDIFIN_INTERNAL:
			snd_iprintf(buffer, "IEC958 input: Internal\n");
			break;
		case HDSP_SPDIFIN_AES:
			snd_iprintf(buffer, "IEC958 input: AES\n");
			break;
		default:
			snd_iprintf(buffer, "IEC958 input: ???\n");
			break;
		}
	}

	if (RPM == hdsp->io_type) {
		if (hdsp->control_register & HDSP_RPM_Bypass)
			snd_iprintf(buffer, "RPM Bypass: disabled\n");
		else
			snd_iprintf(buffer, "RPM Bypass: enabled\n");
		if (hdsp->control_register & HDSP_RPM_Disconnect)
			snd_iprintf(buffer, "RPM disconnected\n");
		else
			snd_iprintf(buffer, "RPM connected\n");

		switch (hdsp->control_register & HDSP_RPM_Inp12) {
		case HDSP_RPM_Inp12_Phon_6dB:
			snd_iprintf(buffer, "Input 1/2: Phono, 6dB\n");
			break;
		case HDSP_RPM_Inp12_Phon_0dB:
			snd_iprintf(buffer, "Input 1/2: Phono, 0dB\n");
			break;
		case HDSP_RPM_Inp12_Phon_n6dB:
			snd_iprintf(buffer, "Input 1/2: Phono, -6dB\n");
			break;
		case HDSP_RPM_Inp12_Line_0dB:
			snd_iprintf(buffer, "Input 1/2: Line, 0dB\n");
			break;
		case HDSP_RPM_Inp12_Line_n6dB:
			snd_iprintf(buffer, "Input 1/2: Line, -6dB\n");
			break;
		default:
			snd_iprintf(buffer, "Input 1/2: ???\n");
		}

		switch (hdsp->control_register & HDSP_RPM_Inp34) {
		case HDSP_RPM_Inp34_Phon_6dB:
			snd_iprintf(buffer, "Input 3/4: Phono, 6dB\n");
			break;
		case HDSP_RPM_Inp34_Phon_0dB:
			snd_iprintf(buffer, "Input 3/4: Phono, 0dB\n");
			break;
		case HDSP_RPM_Inp34_Phon_n6dB:
			snd_iprintf(buffer, "Input 3/4: Phono, -6dB\n");
			break;
		case HDSP_RPM_Inp34_Line_0dB:
			snd_iprintf(buffer, "Input 3/4: Line, 0dB\n");
			break;
		case HDSP_RPM_Inp34_Line_n6dB:
			snd_iprintf(buffer, "Input 3/4: Line, -6dB\n");
			break;
		default:
			snd_iprintf(buffer, "Input 3/4: ???\n");
		}

	} else {
		if (hdsp->control_register & HDSP_SPDIFOpticalOut)
			snd_iprintf(buffer, "IEC958 output: Coaxial & ADAT1\n");
		else
			snd_iprintf(buffer, "IEC958 output: Coaxial only\n");

		if (hdsp->control_register & HDSP_SPDIFProfessional)
			snd_iprintf(buffer, "IEC958 quality: Professional\n");
		else
			snd_iprintf(buffer, "IEC958 quality: Consumer\n");

		if (hdsp->control_register & HDSP_SPDIFEmphasis)
			snd_iprintf(buffer, "IEC958 emphasis: on\n");
		else
			snd_iprintf(buffer, "IEC958 emphasis: off\n");

		if (hdsp->control_register & HDSP_SPDIFNonAudio)
			snd_iprintf(buffer, "IEC958 NonAudio: on\n");
		else
			snd_iprintf(buffer, "IEC958 NonAudio: off\n");
		x = hdsp_spdif_sample_rate(hdsp);
		if (x != 0)
			snd_iprintf(buffer, "IEC958 sample rate: %d\n", x);
		else
			snd_iprintf(buffer, "IEC958 sample rate: Error flag set\n");
	}
	snd_iprintf(buffer, "\n");

	/* Sync Check */
	x = status & HDSP_Sync0;
	if (status & HDSP_Lock0)
		snd_iprintf(buffer, "ADAT1: %s\n", x ? "Sync" : "Lock");
	else
		snd_iprintf(buffer, "ADAT1: No Lock\n");

	switch (hdsp->io_type) {
	case Digiface:
	case H9652:
		x = status & HDSP_Sync1;
		if (status & HDSP_Lock1)
			snd_iprintf(buffer, "ADAT2: %s\n", x ? "Sync" : "Lock");
		else
			snd_iprintf(buffer, "ADAT2: No Lock\n");
		x = status & HDSP_Sync2;
		if (status & HDSP_Lock2)
			snd_iprintf(buffer, "ADAT3: %s\n", x ? "Sync" : "Lock");
		else
			snd_iprintf(buffer, "ADAT3: No Lock\n");
		break;
	default:
		/* relax */
		break;
	}

	x = status & HDSP_SPDIFSync;
	if (status & HDSP_SPDIFErrorFlag)
		snd_iprintf (buffer, "SPDIF: No Lock\n");
	else
		snd_iprintf (buffer, "SPDIF: %s\n", x ? "Sync" : "Lock");

	x = status2 & HDSP_wc_sync;
	if (status2 & HDSP_wc_lock)
		snd_iprintf (buffer, "Word Clock: %s\n", x ? "Sync" : "Lock");
	else
		snd_iprintf (buffer, "Word Clock: No Lock\n");

	x = status & HDSP_TimecodeSync;
	if (status & HDSP_TimecodeLock)
		snd_iprintf(buffer, "ADAT Sync: %s\n", x ? "Sync" : "Lock");
	else
		snd_iprintf(buffer, "ADAT Sync: No Lock\n");

	snd_iprintf(buffer, "\n");

	/* Informations about H9632 specific controls */
	if (hdsp->io_type == H9632) {
		char *tmp;

		switch (hdsp_ad_gain(hdsp)) {
		case 0:
			tmp = "-10 dBV";
			break;
		case 1:
			tmp = "+4 dBu";
			break;
		default:
			tmp = "Lo Gain";
			break;
		}
		snd_iprintf(buffer, "AD Gain : %s\n", tmp);

		switch (hdsp_da_gain(hdsp)) {
		case 0:
			tmp = "Hi Gain";
			break;
		case 1:
			tmp = "+4 dBu";
			break;
		default:
			tmp = "-10 dBV";
			break;
		}
		snd_iprintf(buffer, "DA Gain : %s\n", tmp);

		switch (hdsp_phone_gain(hdsp)) {
		case 0:
			tmp = "0 dB";
			break;
		case 1:
			tmp = "-6 dB";
			break;
		default:
			tmp = "-12 dB";
			break;
		}
		snd_iprintf(buffer, "Phones Gain : %s\n", tmp);

		snd_iprintf(buffer, "XLR Breakout Cable : %s\n",
			hdsp_toggle_setting(hdsp, HDSP_XLRBreakoutCable) ?
			"yes" : "no");

		if (hdsp->control_register & HDSP_AnalogExtensionBoard)
			snd_iprintf(buffer, "AEB : on (ADAT1 internal)\n");
		else
			snd_iprintf(buffer, "AEB : off (ADAT1 external)\n");
		snd_iprintf(buffer, "\n");
	}

}