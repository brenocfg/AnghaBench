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
struct hda_bus {int dummy; } ;
struct sof_intel_hda_dev {struct hda_bus hbus; } ;
struct snd_sof_dev {TYPE_1__* pdata; } ;
struct TYPE_2__ {struct sof_intel_hda_dev* hw_pdata; } ;

/* Variables and functions */

__attribute__((used)) static inline struct hda_bus *sof_to_hbus(struct snd_sof_dev *s)
{
	struct sof_intel_hda_dev *hda = s->pdata->hw_pdata;

	return &hda->hbus;
}