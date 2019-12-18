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
typedef  int u16 ;
struct sof_ipc_comp {int /*<<< orphan*/  type; } ;
struct snd_sof_widget {TYPE_1__* widget; struct sof_ipc_comp* private; int /*<<< orphan*/  id; } ;
struct snd_sof_dev {int /*<<< orphan*/  dev; } ;
struct TYPE_2__ {int /*<<< orphan*/  name; } ;

/* Variables and functions */
 int /*<<< orphan*/  ARRAY_SIZE (int /*<<< orphan*/ ) ; 
 int EINVAL ; 
 int /*<<< orphan*/  SOF_COMP_KEYWORD_DETECT ; 
#define  SOF_KEYWORD_DETECT_DAPM_EVENT 128 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  snd_soc_dapm_effect ; 
 int snd_soc_tplg_widget_bind_event (TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  sof_kwd_events ; 

__attribute__((used)) static int sof_widget_bind_event(struct snd_sof_dev *sdev,
				 struct snd_sof_widget *swidget,
				 u16 event_type)
{
	struct sof_ipc_comp *ipc_comp;

	/* validate widget event type */
	switch (event_type) {
	case SOF_KEYWORD_DETECT_DAPM_EVENT:
		/* only KEYWORD_DETECT comps should handle this */
		if (swidget->id != snd_soc_dapm_effect)
			break;

		ipc_comp = swidget->private;
		if (ipc_comp && ipc_comp->type != SOF_COMP_KEYWORD_DETECT)
			break;

		/* bind event to keyword detect comp */
		return snd_soc_tplg_widget_bind_event(swidget->widget,
						      sof_kwd_events,
						      ARRAY_SIZE(sof_kwd_events),
						      event_type);
	default:
		break;
	}

	dev_err(sdev->dev,
		"error: invalid event type %d for widget %s\n",
		event_type, swidget->widget->name);
	return -EINVAL;
}