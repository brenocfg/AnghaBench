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
struct timestamp_event_queue {int dummy; } ;

/* Variables and functions */
 int PTP_MAX_TIMESTAMPS ; 
 int queue_cnt (struct timestamp_event_queue*) ; 

__attribute__((used)) static inline int queue_free(struct timestamp_event_queue *q)
{
	return PTP_MAX_TIMESTAMPS - queue_cnt(q) - 1;
}