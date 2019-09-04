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
typedef  union evrec {int dummy; } evrec ;
struct snd_seq_event {int /*<<< orphan*/  data; int /*<<< orphan*/  type; } ;
struct TYPE_2__ {int /*<<< orphan*/  port; int /*<<< orphan*/  client; } ;
struct seq_oss_devinfo {TYPE_1__ addr; } ;

/* Variables and functions */
 int /*<<< orphan*/  LONG_EVENT_SIZE ; 
 int /*<<< orphan*/  SNDRV_SEQ_EVENT_ECHO ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,union evrec*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  snd_seq_oss_fill_addr (struct seq_oss_devinfo*,struct snd_seq_event*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
set_echo_event(struct seq_oss_devinfo *dp, union evrec *rec, struct snd_seq_event *ev)
{
	ev->type = SNDRV_SEQ_EVENT_ECHO;
	/* echo back to itself */
	snd_seq_oss_fill_addr(dp, ev, dp->addr.client, dp->addr.port);
	memcpy(&ev->data, rec, LONG_EVENT_SIZE);
	return 0;
}