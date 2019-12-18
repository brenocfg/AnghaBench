#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct snd_sof_widget {int /*<<< orphan*/  comp_id; } ;
struct TYPE_5__ {TYPE_1__* caps; } ;
struct snd_sof_pcm {TYPE_3__* stream; TYPE_2__ pcm; } ;
struct snd_sof_dev {int /*<<< orphan*/  dev; } ;
struct TYPE_6__ {int /*<<< orphan*/  comp_id; } ;
struct TYPE_4__ {int /*<<< orphan*/  name; } ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*) ; 
 struct snd_sof_widget* snd_sof_find_swidget_sname (struct snd_sof_dev*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int spcm_bind(struct snd_sof_dev *sdev, struct snd_sof_pcm *spcm,
		     int dir)
{
	struct snd_sof_widget *host_widget;

	host_widget = snd_sof_find_swidget_sname(sdev,
						 spcm->pcm.caps[dir].name,
						 dir);
	if (!host_widget) {
		dev_err(sdev->dev, "can't find host comp to bind pcm\n");
		return -EINVAL;
	}

	spcm->stream[dir].comp_id = host_widget->comp_id;

	return 0;
}