#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int /*<<< orphan*/  set_pro_rate; } ;
struct snd_ice1712 {int num_total_dacs; int num_total_adcs; TYPE_2__* card; TYPE_1__ gpio; struct prodigy192_spec* spec; scalar_t__ vt1720; } ;
struct prodigy192_spec {int /*<<< orphan*/  mute_mutex; } ;
struct TYPE_4__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
#define  STAC946X_MASTER_CLOCKING 129 
#define  STAC946X_RESET 128 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ ,char*,...) ; 
 struct prodigy192_spec* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mutex_init (int /*<<< orphan*/ *) ; 
 int prodigy192_ak4114_init (struct snd_ice1712*) ; 
 scalar_t__ prodigy192_miodio_exists (struct snd_ice1712*) ; 
 int /*<<< orphan*/  stac9460_put (struct snd_ice1712*,unsigned short const,unsigned short const) ; 
 int /*<<< orphan*/  stac9460_set_rate_val ; 

__attribute__((used)) static int prodigy192_init(struct snd_ice1712 *ice)
{
	static const unsigned short stac_inits_prodigy[] = {
		STAC946X_RESET, 0,
		STAC946X_MASTER_CLOCKING, 0x11,
/*		STAC946X_MASTER_VOLUME, 0,
		STAC946X_LF_VOLUME, 0,
		STAC946X_RF_VOLUME, 0,
		STAC946X_LR_VOLUME, 0,
		STAC946X_RR_VOLUME, 0,
		STAC946X_CENTER_VOLUME, 0,
		STAC946X_LFE_VOLUME, 0,*/
		(unsigned short)-1
	};
	const unsigned short *p;
	int err = 0;
	struct prodigy192_spec *spec;

	/* prodigy 192 */
	ice->num_total_dacs = 6;
	ice->num_total_adcs = 2;
	ice->vt1720 = 0;  /* ice1724, e.g. 23 GPIOs */
	
	spec = kzalloc(sizeof(*spec), GFP_KERNEL);
	if (!spec)
		return -ENOMEM;
	ice->spec = spec;
	mutex_init(&spec->mute_mutex);

	/* initialize codec */
	p = stac_inits_prodigy;
	for (; *p != (unsigned short)-1; p += 2)
		stac9460_put(ice, p[0], p[1]);
	ice->gpio.set_pro_rate = stac9460_set_rate_val;

	/* MI/ODI/O add on card with AK4114 */
	if (prodigy192_miodio_exists(ice)) {
		err = prodigy192_ak4114_init(ice);
		/* from this moment if err = 0 then
		 * spec->ak4114 should not be null
		 */
		dev_dbg(ice->card->dev,
			"AK4114 initialized with status %d\n", err);
	} else
		dev_dbg(ice->card->dev, "AK4114 not found\n");

	return err;
}