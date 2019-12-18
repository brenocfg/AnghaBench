#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int u8 ;
struct amdtp_stream {int dummy; } ;
struct snd_bebob {TYPE_1__* unit; struct amdtp_stream tx_stream; } ;
typedef  enum avc_bridgeco_plug_dir { ____Placeholder_avc_bridgeco_plug_dir } avc_bridgeco_plug_dir ;
struct TYPE_3__ {int /*<<< orphan*/  device; } ;

/* Variables and functions */
 unsigned int AM824_MAX_CHANNELS_FOR_PCM ; 
 int AVC_BRIDGECO_ADDR_BYTES ; 
 int AVC_BRIDGECO_PLUG_DIR_IN ; 
 int AVC_BRIDGECO_PLUG_DIR_OUT ; 
 int /*<<< orphan*/  AVC_BRIDGECO_PLUG_UNIT_ISOC ; 
 int ENOMEM ; 
 int ENOSYS ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  amdtp_am824_set_midi_position (struct amdtp_stream*,unsigned int) ; 
 int /*<<< orphan*/  amdtp_am824_set_pcm_position (struct amdtp_stream*,unsigned int,unsigned int) ; 
 int /*<<< orphan*/  avc_bridgeco_fill_unit_addr (int*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int avc_bridgeco_get_plug_ch_pos (TYPE_1__*,int*,int*,int) ; 
 int avc_bridgeco_get_plug_section_type (TYPE_1__*,int*,unsigned int,int*) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*,char*,int) ; 
 int /*<<< orphan*/  kfree (int*) ; 
 int* kzalloc (int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int map_data_channels(struct snd_bebob *bebob, struct amdtp_stream *s)
{
	unsigned int sec, sections, ch, channels;
	unsigned int pcm, midi, location;
	unsigned int stm_pos, sec_loc, pos;
	u8 *buf, addr[AVC_BRIDGECO_ADDR_BYTES], type;
	enum avc_bridgeco_plug_dir dir;
	int err;

	/*
	 * The length of return value of this command cannot be expected. Here
	 * use the maximum length of FCP.
	 */
	buf = kzalloc(256, GFP_KERNEL);
	if (buf == NULL)
		return -ENOMEM;

	if (s == &bebob->tx_stream)
		dir = AVC_BRIDGECO_PLUG_DIR_OUT;
	else
		dir = AVC_BRIDGECO_PLUG_DIR_IN;

	avc_bridgeco_fill_unit_addr(addr, dir, AVC_BRIDGECO_PLUG_UNIT_ISOC, 0);
	err = avc_bridgeco_get_plug_ch_pos(bebob->unit, addr, buf, 256);
	if (err < 0) {
		dev_err(&bebob->unit->device,
			"fail to get channel position for isoc %s plug 0: %d\n",
			(dir == AVC_BRIDGECO_PLUG_DIR_IN) ? "in" : "out",
			err);
		goto end;
	}
	pos = 0;

	/* positions in I/O buffer */
	pcm = 0;
	midi = 0;

	/* the number of sections in AMDTP packet */
	sections = buf[pos++];

	for (sec = 0; sec < sections; sec++) {
		/* type of this section */
		avc_bridgeco_fill_unit_addr(addr, dir,
					    AVC_BRIDGECO_PLUG_UNIT_ISOC, 0);
		err = avc_bridgeco_get_plug_section_type(bebob->unit, addr,
							 sec, &type);
		if (err < 0) {
			dev_err(&bebob->unit->device,
			"fail to get section type for isoc %s plug 0: %d\n",
				(dir == AVC_BRIDGECO_PLUG_DIR_IN) ? "in" :
								    "out",
				err);
			goto end;
		}
		/* NoType */
		if (type == 0xff) {
			err = -ENOSYS;
			goto end;
		}

		/* the number of channels in this section */
		channels = buf[pos++];

		for (ch = 0; ch < channels; ch++) {
			/* position of this channel in AMDTP packet */
			stm_pos = buf[pos++] - 1;
			/* location of this channel in this section */
			sec_loc = buf[pos++] - 1;

			/*
			 * Basically the number of location is within the
			 * number of channels in this section. But some models
			 * of M-Audio don't follow this. Its location for MIDI
			 * is the position of MIDI channels in AMDTP packet.
			 */
			if (sec_loc >= channels)
				sec_loc = ch;

			switch (type) {
			/* for MIDI conformant data channel */
			case 0x0a:
				/* AMDTP_MAX_CHANNELS_FOR_MIDI is 1. */
				if ((midi > 0) && (stm_pos != midi)) {
					err = -ENOSYS;
					goto end;
				}
				amdtp_am824_set_midi_position(s, stm_pos);
				midi = stm_pos;
				break;
			/* for PCM data channel */
			case 0x01:	/* Headphone */
			case 0x02:	/* Microphone */
			case 0x03:	/* Line */
			case 0x04:	/* SPDIF */
			case 0x05:	/* ADAT */
			case 0x06:	/* TDIF */
			case 0x07:	/* MADI */
			/* for undefined/changeable signal  */
			case 0x08:	/* Analog */
			case 0x09:	/* Digital */
			default:
				location = pcm + sec_loc;
				if (location >= AM824_MAX_CHANNELS_FOR_PCM) {
					err = -ENOSYS;
					goto end;
				}
				amdtp_am824_set_pcm_position(s, location,
							     stm_pos);
				break;
			}
		}

		if (type != 0x0a)
			pcm += channels;
		else
			midi += channels;
	}
end:
	kfree(buf);
	return err;
}