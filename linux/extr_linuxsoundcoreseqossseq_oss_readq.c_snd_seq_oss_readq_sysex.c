#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
struct snd_seq_event {int flags; } ;
struct seq_oss_readq {int dummy; } ;
struct readq_sysex_ctx {int dev; struct seq_oss_readq* readq; } ;

/* Variables and functions */
 int SNDRV_SEQ_EVENT_LENGTH_MASK ; 
 int SNDRV_SEQ_EVENT_LENGTH_VARIABLE ; 
 int /*<<< orphan*/  readq_dump_sysex ; 
 int snd_seq_dump_var_event (struct snd_seq_event*,int /*<<< orphan*/ ,struct readq_sysex_ctx*) ; 

int snd_seq_oss_readq_sysex(struct seq_oss_readq *q, int dev,
			    struct snd_seq_event *ev)
{
	struct readq_sysex_ctx ctx = {
		.readq = q,
		.dev = dev
	};

	if ((ev->flags & SNDRV_SEQ_EVENT_LENGTH_MASK) != SNDRV_SEQ_EVENT_LENGTH_VARIABLE)
		return 0;
	return snd_seq_dump_var_event(ev, readq_dump_sysex, &ctx);
}