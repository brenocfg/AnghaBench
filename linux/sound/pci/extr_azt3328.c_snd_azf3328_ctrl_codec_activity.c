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
struct snd_azf3328_codec_data {int running; int /*<<< orphan*/  name; } ;
struct snd_azf3328 {struct snd_azf3328_codec_data* codecs; TYPE_1__* card; } ;
typedef  enum snd_azf3328_codec_type { ____Placeholder_snd_azf3328_codec_type } snd_azf3328_codec_type ;
struct TYPE_2__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
#define  AZF_CODEC_CAPTURE 130 
#define  AZF_CODEC_I2S_OUT 129 
#define  AZF_CODEC_PLAYBACK 128 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  snd_azf3328_codec_setfmt_lowpower (struct snd_azf3328_codec_data*) ; 
 int /*<<< orphan*/  snd_azf3328_ctrl_enable_codecs (struct snd_azf3328*,int) ; 

__attribute__((used)) static void
snd_azf3328_ctrl_codec_activity(struct snd_azf3328 *chip,
				enum snd_azf3328_codec_type codec_type,
				bool enable
)
{
	struct snd_azf3328_codec_data *codec = &chip->codecs[codec_type];
	bool need_change = (codec->running != enable);

	dev_dbg(chip->card->dev,
		"codec_activity: %s codec, enable %d, need_change %d\n",
				codec->name, enable, need_change
	);
	if (need_change) {
		static const struct {
			enum snd_azf3328_codec_type other1;
			enum snd_azf3328_codec_type other2;
		} peer_codecs[3] =
			{ { AZF_CODEC_CAPTURE, AZF_CODEC_I2S_OUT },
			  { AZF_CODEC_PLAYBACK, AZF_CODEC_I2S_OUT },
			  { AZF_CODEC_PLAYBACK, AZF_CODEC_CAPTURE } };
		bool call_function;

		if (enable)
			/* if enable codec, call enable_codecs func
			   to enable codec supply... */
			call_function = 1;
		else {
			/* ...otherwise call enable_codecs func
			   (which globally shuts down operation of codecs)
			   only in case the other codecs are currently
			   not active either! */
			call_function =
				((!chip->codecs[peer_codecs[codec_type].other1]
					.running)
			     &&  (!chip->codecs[peer_codecs[codec_type].other2]
					.running));
		}
		if (call_function)
			snd_azf3328_ctrl_enable_codecs(chip, enable);

		/* ...and adjust clock, too
		 * (reduce noise and power consumption) */
		if (!enable)
			snd_azf3328_codec_setfmt_lowpower(codec);
		codec->running = enable;
	}
}