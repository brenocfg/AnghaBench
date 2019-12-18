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
struct TYPE_2__ {int /*<<< orphan*/  (* block_read ) (struct snd_sof_dev*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,void*,size_t) ;} ;

/* Variables and functions */
 TYPE_1__* sof_ops (struct snd_sof_dev*) ; 
 int /*<<< orphan*/  stub1 (struct snd_sof_dev*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,void*,size_t) ; 

__attribute__((used)) static inline void snd_sof_dsp_block_read(struct snd_sof_dev *sdev, u32 bar,
					  u32 offset, void *dest, size_t bytes)
{
	sof_ops(sdev)->block_read(sdev, bar, offset, dest, bytes);
}