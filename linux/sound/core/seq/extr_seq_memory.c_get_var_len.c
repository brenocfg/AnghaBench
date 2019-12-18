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
struct TYPE_3__ {int len; } ;
struct TYPE_4__ {TYPE_1__ ext; } ;
struct snd_seq_event {int flags; TYPE_2__ data; } ;

/* Variables and functions */
 int EINVAL ; 
 int SNDRV_SEQ_EVENT_LENGTH_MASK ; 
 int SNDRV_SEQ_EVENT_LENGTH_VARIABLE ; 
 int SNDRV_SEQ_EXT_MASK ; 

__attribute__((used)) static int get_var_len(const struct snd_seq_event *event)
{
	if ((event->flags & SNDRV_SEQ_EVENT_LENGTH_MASK) != SNDRV_SEQ_EVENT_LENGTH_VARIABLE)
		return -EINVAL;

	return event->data.ext.len & ~SNDRV_SEQ_EXT_MASK;
}