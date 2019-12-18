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
struct snd_sof_ipc_msg {int dummy; } ;
struct snd_sof_dev {int dummy; } ;
struct TYPE_2__ {int (* send_msg ) (struct snd_sof_dev*,struct snd_sof_ipc_msg*) ;} ;

/* Variables and functions */
 TYPE_1__* sof_ops (struct snd_sof_dev*) ; 
 int stub1 (struct snd_sof_dev*,struct snd_sof_ipc_msg*) ; 

__attribute__((used)) static inline int snd_sof_dsp_send_msg(struct snd_sof_dev *sdev,
				       struct snd_sof_ipc_msg *msg)
{
	return sof_ops(sdev)->send_msg(sdev, msg);
}