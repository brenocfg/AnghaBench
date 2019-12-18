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
struct snd_seq_event {int dummy; } ;
struct seq_oss_devinfo {int /*<<< orphan*/  cseq; } ;

/* Variables and functions */
 int snd_seq_kernel_client_dispatch (int /*<<< orphan*/ ,struct snd_seq_event*,int,int) ; 

__attribute__((used)) static inline int
snd_seq_oss_dispatch(struct seq_oss_devinfo *dp, struct snd_seq_event *ev, int atomic, int hop)
{
	return snd_seq_kernel_client_dispatch(dp->cseq, ev, atomic, hop);
}