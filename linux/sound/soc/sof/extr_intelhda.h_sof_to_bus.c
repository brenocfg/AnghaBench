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
struct hdac_bus {int dummy; } ;
struct TYPE_4__ {struct hdac_bus core; } ;
struct sof_intel_hda_dev {TYPE_2__ hbus; } ;
struct snd_sof_dev {TYPE_1__* pdata; } ;
struct TYPE_3__ {struct sof_intel_hda_dev* hw_pdata; } ;

/* Variables and functions */

__attribute__((used)) static inline struct hdac_bus *sof_to_bus(struct snd_sof_dev *s)
{
	struct sof_intel_hda_dev *hda = s->pdata->hw_pdata;

	return &hda->hbus.core;
}