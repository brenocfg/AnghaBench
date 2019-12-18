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
typedef  int /*<<< orphan*/  u32 ;
struct snd_sof_dev {int dummy; } ;
struct TYPE_2__ {void (* dbg_dump ) (struct snd_sof_dev*,int /*<<< orphan*/ ) ;} ;

/* Variables and functions */
 TYPE_1__* sof_ops (struct snd_sof_dev*) ; 
 void stub1 (struct snd_sof_dev*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline void snd_sof_dsp_dbg_dump(struct snd_sof_dev *sdev, u32 flags)
{
	if (sof_ops(sdev)->dbg_dump)
		return sof_ops(sdev)->dbg_dump(sdev, flags);
}