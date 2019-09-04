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
struct snd_dbri {TYPE_1__* stream_info; } ;
struct snd_card {int /*<<< orphan*/  shortname; int /*<<< orphan*/  mixername; struct snd_dbri* private_data; } ;
struct TYPE_2__ {scalar_t__ right_gain; scalar_t__ left_gain; } ;

/* Variables and functions */
 int ARRAY_SIZE (int /*<<< orphan*/ *) ; 
 int DBRI_NO_STREAMS ; 
 int DBRI_REC ; 
 int EINVAL ; 
 int /*<<< orphan*/ * dbri_controls ; 
 scalar_t__ snd_BUG_ON (int) ; 
 int snd_ctl_add (struct snd_card*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  snd_ctl_new1 (int /*<<< orphan*/ *,struct snd_dbri*) ; 
 int /*<<< orphan*/  strcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int snd_dbri_mixer(struct snd_card *card)
{
	int idx, err;
	struct snd_dbri *dbri;

	if (snd_BUG_ON(!card || !card->private_data))
		return -EINVAL;
	dbri = card->private_data;

	strcpy(card->mixername, card->shortname);

	for (idx = 0; idx < ARRAY_SIZE(dbri_controls); idx++) {
		err = snd_ctl_add(card,
				snd_ctl_new1(&dbri_controls[idx], dbri));
		if (err < 0)
			return err;
	}

	for (idx = DBRI_REC; idx < DBRI_NO_STREAMS; idx++) {
		dbri->stream_info[idx].left_gain = 0;
		dbri->stream_info[idx].right_gain = 0;
	}

	return 0;
}