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
struct snd_sof_dev {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  (* dsp_oops ) (struct snd_sof_dev*,void*) ;} ;

/* Variables and functions */
 TYPE_1__* sof_arch_ops (struct snd_sof_dev*) ; 
 int /*<<< orphan*/  stub1 (struct snd_sof_dev*,void*) ; 

__attribute__((used)) static inline void sof_oops(struct snd_sof_dev *sdev, void *oops)
{
	if (sof_arch_ops(sdev)->dsp_oops)
		sof_arch_ops(sdev)->dsp_oops(sdev, oops);
}