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
struct snd_soc_dapm_widget {TYPE_2__* dapm; int /*<<< orphan*/  dirty; int /*<<< orphan*/  name; } ;
struct TYPE_4__ {TYPE_1__* card; int /*<<< orphan*/  dev; } ;
struct TYPE_3__ {int /*<<< orphan*/  dapm_dirty; } ;

/* Variables and functions */
 int /*<<< orphan*/  dapm_assert_locked (TYPE_2__*) ; 
 int /*<<< orphan*/  dapm_dirty_widget (struct snd_soc_dapm_widget*) ; 
 int /*<<< orphan*/  dev_vdbg (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,char const*) ; 
 int /*<<< orphan*/  list_add_tail (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void dapm_mark_dirty(struct snd_soc_dapm_widget *w, const char *reason)
{
	dapm_assert_locked(w->dapm);

	if (!dapm_dirty_widget(w)) {
		dev_vdbg(w->dapm->dev, "Marking %s dirty due to %s\n",
			 w->name, reason);
		list_add_tail(&w->dirty, &w->dapm->card->dapm_dirty);
	}
}