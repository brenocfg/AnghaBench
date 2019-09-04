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
struct msg_queue {scalar_t__ q_cbytes; scalar_t__ q_qbytes; scalar_t__ q_qnum; } ;

/* Variables and functions */

__attribute__((used)) static inline bool msg_fits_inqueue(struct msg_queue *msq, size_t msgsz)
{
	return msgsz + msq->q_cbytes <= msq->q_qbytes &&
		1 + msq->q_qnum <= msq->q_qbytes;
}