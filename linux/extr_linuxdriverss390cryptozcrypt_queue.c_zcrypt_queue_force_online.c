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
struct zcrypt_queue {int online; int /*<<< orphan*/  queue; } ;

/* Variables and functions */
 int /*<<< orphan*/  ap_flush_queue (int /*<<< orphan*/ ) ; 

void zcrypt_queue_force_online(struct zcrypt_queue *zq, int online)
{
	zq->online = online;
	if (!online)
		ap_flush_queue(zq->queue);
}