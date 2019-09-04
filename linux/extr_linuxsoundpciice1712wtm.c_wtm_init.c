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
struct wtm_spec {int /*<<< orphan*/  mute_mutex; } ;
struct TYPE_2__ {int /*<<< orphan*/  set_pro_rate; } ;
struct snd_ice1712 {int num_total_dacs; int num_total_adcs; int force_rdma1; TYPE_1__ gpio; struct wtm_spec* spec; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
#define  STAC946X_MASTER_CLOCKING 129 
#define  STAC946X_RESET 128 
 struct wtm_spec* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mutex_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stac9460_2_put (struct snd_ice1712*,unsigned short,unsigned short) ; 
 int /*<<< orphan*/  stac9460_put (struct snd_ice1712*,unsigned short,unsigned short) ; 
 int /*<<< orphan*/  stac9460_set_rate_val ; 

__attribute__((used)) static int wtm_init(struct snd_ice1712 *ice)
{
	static unsigned short stac_inits_wtm[] = {
		STAC946X_RESET, 0,
		STAC946X_MASTER_CLOCKING, 0x11,
		(unsigned short)-1
	};
	unsigned short *p;
	struct wtm_spec *spec;

	/*WTM 192M*/
	ice->num_total_dacs = 8;
	ice->num_total_adcs = 4;
	ice->force_rdma1 = 1;

	/*init mutex for dac mute conflict*/
	spec = kzalloc(sizeof(*spec), GFP_KERNEL);
	if (!spec)
		return -ENOMEM;
	ice->spec = spec;
	mutex_init(&spec->mute_mutex);


	/*initialize codec*/
	p = stac_inits_wtm;
	for (; *p != (unsigned short)-1; p += 2) {
		stac9460_put(ice, p[0], p[1]);
		stac9460_2_put(ice, p[0], p[1]);
	}
	ice->gpio.set_pro_rate = stac9460_set_rate_val;
	return 0;
}