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
struct snd_pcm_substream {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  (* ipc_msg_data ) (struct snd_sof_dev*,struct snd_pcm_substream*,void*,size_t) ;} ;

/* Variables and functions */
 TYPE_1__* sof_ops (struct snd_sof_dev*) ; 
 int /*<<< orphan*/  stub1 (struct snd_sof_dev*,struct snd_pcm_substream*,void*,size_t) ; 

__attribute__((used)) static inline void snd_sof_ipc_msg_data(struct snd_sof_dev *sdev,
					struct snd_pcm_substream *substream,
					void *p, size_t sz)
{
	sof_ops(sdev)->ipc_msg_data(sdev, substream, p, sz);
}