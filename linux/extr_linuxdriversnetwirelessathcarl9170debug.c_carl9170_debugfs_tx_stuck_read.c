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
struct ar9170 {scalar_t__* max_queue_stop_timeout; scalar_t__* queue_stop_timeout; TYPE_1__* hw; } ;
typedef  int /*<<< orphan*/  ssize_t ;
struct TYPE_2__ {int queues; } ;

/* Variables and functions */
 int /*<<< orphan*/  ADD (char*,int /*<<< orphan*/ ,size_t,char*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ ieee80211_queue_stopped (TYPE_1__*,int) ; 
 scalar_t__ jiffies ; 
 int /*<<< orphan*/  jiffies_to_msecs (scalar_t__) ; 

__attribute__((used)) static char *carl9170_debugfs_tx_stuck_read(struct ar9170 *ar, char *buf,
					    size_t bufsize, ssize_t *len)
{
	int i;

	for (i = 0; i < ar->hw->queues; i++) {
		ADD(buf, *len, bufsize, "TX queue [%d]: %10d max:%10d ms.\n",
		    i, ieee80211_queue_stopped(ar->hw, i) ?
		    jiffies_to_msecs(jiffies - ar->queue_stop_timeout[i]) : 0,
		    jiffies_to_msecs(ar->max_queue_stop_timeout[i]));

		ar->max_queue_stop_timeout[i] = 0;
	}

	return buf;
}