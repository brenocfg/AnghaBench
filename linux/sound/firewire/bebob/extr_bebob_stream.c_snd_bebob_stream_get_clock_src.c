#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int u8 ;
struct snd_bebob_clock_spec {int (* get ) (struct snd_bebob*,unsigned int*) ;unsigned int num; int* types; } ;
struct snd_bebob {unsigned int sync_input_plug; TYPE_2__* unit; TYPE_1__* spec; } ;
typedef  enum snd_bebob_clock_type { ____Placeholder_snd_bebob_clock_type } snd_bebob_clock_type ;
typedef  enum avc_bridgeco_plug_type { ____Placeholder_avc_bridgeco_plug_type } avc_bridgeco_plug_type ;
struct TYPE_5__ {int /*<<< orphan*/  device; } ;
struct TYPE_4__ {struct snd_bebob_clock_spec* clock; } ;

/* Variables and functions */
 int AVC_BRIDGECO_ADDR_BYTES ; 
 int /*<<< orphan*/  AVC_BRIDGECO_PLUG_DIR_IN ; 
 int AVC_BRIDGECO_PLUG_DIR_OUT ; 
 int AVC_BRIDGECO_PLUG_MODE_SUBUNIT ; 
 int AVC_BRIDGECO_PLUG_MODE_UNIT ; 
 int AVC_BRIDGECO_PLUG_TYPE_ADDITION ; 
 int AVC_BRIDGECO_PLUG_TYPE_DIG ; 
 int AVC_BRIDGECO_PLUG_TYPE_SYNC ; 
 int AVC_BRIDGECO_PLUG_UNIT_EXT ; 
 int AVC_BRIDGECO_PLUG_UNIT_ISOC ; 
 int EIO ; 
 int SND_BEBOB_CLOCK_TYPE_EXTERNAL ; 
 int SND_BEBOB_CLOCK_TYPE_INTERNAL ; 
 int SND_BEBOB_CLOCK_TYPE_SYT ; 
 int /*<<< orphan*/  avc_bridgeco_fill_msu_addr (int*,int /*<<< orphan*/ ,unsigned int) ; 
 int /*<<< orphan*/  avc_bridgeco_fill_unit_addr (int*,int /*<<< orphan*/ ,int,int) ; 
 int avc_bridgeco_get_plug_input (TYPE_2__*,int*,int*) ; 
 int avc_bridgeco_get_plug_type (TYPE_2__*,int*,int*) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*,unsigned int,...) ; 
 int stub1 (struct snd_bebob*,unsigned int*) ; 

int snd_bebob_stream_get_clock_src(struct snd_bebob *bebob,
				   enum snd_bebob_clock_type *src)
{
	const struct snd_bebob_clock_spec *clk_spec = bebob->spec->clock;
	u8 addr[AVC_BRIDGECO_ADDR_BYTES], input[7];
	unsigned int id;
	enum avc_bridgeco_plug_type type;
	int err = 0;

	/* 1.The device has its own operation to switch source of clock */
	if (clk_spec) {
		err = clk_spec->get(bebob, &id);
		if (err < 0) {
			dev_err(&bebob->unit->device,
				"fail to get clock source: %d\n", err);
			goto end;
		}

		if (id >= clk_spec->num) {
			dev_err(&bebob->unit->device,
				"clock source %d out of range 0..%d\n",
				id, clk_spec->num - 1);
			err = -EIO;
			goto end;
		}

		*src = clk_spec->types[id];
		goto end;
	}

	/*
	 * 2.The device don't support to switch source of clock then assumed
	 *   to use internal clock always
	 */
	if (bebob->sync_input_plug < 0) {
		*src = SND_BEBOB_CLOCK_TYPE_INTERNAL;
		goto end;
	}

	/*
	 * 3.The device supports to switch source of clock by an usual way.
	 *   Let's check input for 'Music Sub Unit Sync Input' plug.
	 */
	avc_bridgeco_fill_msu_addr(addr, AVC_BRIDGECO_PLUG_DIR_IN,
				   bebob->sync_input_plug);
	err = avc_bridgeco_get_plug_input(bebob->unit, addr, input);
	if (err < 0) {
		dev_err(&bebob->unit->device,
			"fail to get an input for MSU in plug %d: %d\n",
			bebob->sync_input_plug, err);
		goto end;
	}

	/*
	 * If there are no input plugs, all of fields are 0xff.
	 * Here check the first field. This field is used for direction.
	 */
	if (input[0] == 0xff) {
		*src = SND_BEBOB_CLOCK_TYPE_INTERNAL;
		goto end;
	}

	/* The source from any output plugs is for one purpose only. */
	if (input[0] == AVC_BRIDGECO_PLUG_DIR_OUT) {
		/*
		 * In BeBoB architecture, the source from music subunit may
		 * bypass from oPCR[0]. This means that this source gives
		 * synchronization to IEEE 1394 cycle start packet.
		 */
		if (input[1] == AVC_BRIDGECO_PLUG_MODE_SUBUNIT &&
		    input[2] == 0x0c) {
			*src = SND_BEBOB_CLOCK_TYPE_INTERNAL;
			goto end;
		}
	/* The source from any input units is for several purposes. */
	} else if (input[1] == AVC_BRIDGECO_PLUG_MODE_UNIT) {
		if (input[2] == AVC_BRIDGECO_PLUG_UNIT_ISOC) {
			if (input[3] == 0x00) {
				/*
				 * This source comes from iPCR[0]. This means
				 * that presentation timestamp calculated by
				 * SYT series of the received packets. In
				 * short, this driver is the master of
				 * synchronization.
				 */
				*src = SND_BEBOB_CLOCK_TYPE_SYT;
				goto end;
			} else {
				/*
				 * This source comes from iPCR[1-29]. This
				 * means that the synchronization stream is not
				 * the Audio/MIDI compound stream.
				 */
				*src = SND_BEBOB_CLOCK_TYPE_EXTERNAL;
				goto end;
			}
		} else if (input[2] == AVC_BRIDGECO_PLUG_UNIT_EXT) {
			/* Check type of this plug.  */
			avc_bridgeco_fill_unit_addr(addr,
						    AVC_BRIDGECO_PLUG_DIR_IN,
						    AVC_BRIDGECO_PLUG_UNIT_EXT,
						    input[3]);
			err = avc_bridgeco_get_plug_type(bebob->unit, addr,
							 &type);
			if (err < 0)
				goto end;

			if (type == AVC_BRIDGECO_PLUG_TYPE_DIG) {
				/*
				 * SPDIF/ADAT or sometimes (not always) word
				 * clock.
				 */
				*src = SND_BEBOB_CLOCK_TYPE_EXTERNAL;
				goto end;
			} else if (type == AVC_BRIDGECO_PLUG_TYPE_SYNC) {
				/* Often word clock. */
				*src = SND_BEBOB_CLOCK_TYPE_EXTERNAL;
				goto end;
			} else if (type == AVC_BRIDGECO_PLUG_TYPE_ADDITION) {
				/*
				 * Not standard.
				 * Mostly, additional internal clock.
				 */
				*src = SND_BEBOB_CLOCK_TYPE_INTERNAL;
				goto end;
			}
		}
	}

	/* Not supported. */
	err = -EIO;
end:
	return err;
}