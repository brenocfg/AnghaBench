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
struct TYPE_2__ {int /*<<< orphan*/  dest_phys_out_ofs; int /*<<< orphan*/  dest_phys_outs; int /*<<< orphan*/  src_stream_out_ofs; int /*<<< orphan*/  src_stream_outs; int /*<<< orphan*/  src_phys_ins; int /*<<< orphan*/  dest_stream_ins; } ;
struct lola {TYPE_1__ mixer; } ;

/* Variables and functions */
 int /*<<< orphan*/  CAPT ; 
 int /*<<< orphan*/  PLAY ; 
 int create_analog_mixer (struct lola*,int /*<<< orphan*/ ,char*) ; 
 int create_dest_gain_mixer (struct lola*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 
 int create_input_src_mixer (struct lola*) ; 
 int create_src_gain_mixer (struct lola*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 
 int init_mixer_values (struct lola*) ; 

int lola_create_mixer(struct lola *chip)
{
	int err;

	err = create_analog_mixer(chip, PLAY, "Analog Playback Volume");
	if (err < 0)
		return err;
	err = create_analog_mixer(chip, CAPT, "Analog Capture Volume");
	if (err < 0)
		return err;
	err = create_input_src_mixer(chip);
	if (err < 0)
		return err;
	err = create_src_gain_mixer(chip, chip->mixer.src_phys_ins, 0,
				    "Digital Capture Volume");
	if (err < 0)
		return err;
	err = create_src_gain_mixer(chip, chip->mixer.src_stream_outs,
				    chip->mixer.src_stream_out_ofs,
				    "Digital Playback Volume");
	if (err < 0)
		return err;
#if 0
/* FIXME: buggy mixer matrix handling */
	err = create_dest_gain_mixer(chip,
				     chip->mixer.src_phys_ins, 0,
				     chip->mixer.dest_stream_ins, 0,
				     "Line Capture Volume");
	if (err < 0)
		return err;
	err = create_dest_gain_mixer(chip,
				     chip->mixer.src_stream_outs,
				     chip->mixer.src_stream_out_ofs,
				     chip->mixer.dest_stream_ins, 0,
				     "Stream-Loopback Capture Volume");
	if (err < 0)
		return err;
	err = create_dest_gain_mixer(chip,
				     chip->mixer.src_phys_ins, 0,
				     chip->mixer.dest_phys_outs,
				     chip->mixer.dest_phys_out_ofs,
				     "Line-Loopback Playback Volume");
	if (err < 0)
		return err;
	err = create_dest_gain_mixer(chip,
				     chip->mixer.src_stream_outs,
				     chip->mixer.src_stream_out_ofs,
				     chip->mixer.dest_phys_outs,
				     chip->mixer.dest_phys_out_ofs,
				     "Stream Playback Volume");
	if (err < 0)
		return err;
#endif /* FIXME */
	return init_mixer_values(chip);
}