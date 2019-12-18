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
struct intel8x0m {int device_type; int pcm_devs; TYPE_1__* ichd; } ;
struct ich_pcm_table {size_t ac97_idx; } ;
struct TYPE_2__ {int /*<<< orphan*/  ac97; } ;

/* Variables and functions */
 int ARRAY_SIZE (struct ich_pcm_table*) ; 
#define  DEVICE_ALI 129 
#define  DEVICE_NFORCE 128 
 struct ich_pcm_table* ali_pcms ; 
 struct ich_pcm_table* intel_pcms ; 
 struct ich_pcm_table* nforce_pcms ; 
 int snd_intel8x0m_pcm1 (struct intel8x0m*,int,struct ich_pcm_table*) ; 

__attribute__((used)) static int snd_intel8x0m_pcm(struct intel8x0m *chip)
{
	int i, tblsize, device, err;
	struct ich_pcm_table *tbl, *rec;

#if 1
	tbl = intel_pcms;
	tblsize = 1;
#else
	switch (chip->device_type) {
	case DEVICE_NFORCE:
		tbl = nforce_pcms;
		tblsize = ARRAY_SIZE(nforce_pcms);
		break;
	case DEVICE_ALI:
		tbl = ali_pcms;
		tblsize = ARRAY_SIZE(ali_pcms);
		break;
	default:
		tbl = intel_pcms;
		tblsize = 2;
		break;
	}
#endif
	device = 0;
	for (i = 0; i < tblsize; i++) {
		rec = tbl + i;
		if (i > 0 && rec->ac97_idx) {
			/* activate PCM only when associated AC'97 codec */
			if (! chip->ichd[rec->ac97_idx].ac97)
				continue;
		}
		err = snd_intel8x0m_pcm1(chip, device, rec);
		if (err < 0)
			return err;
		device++;
	}

	chip->pcm_devs = device;
	return 0;
}