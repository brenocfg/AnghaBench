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
struct TYPE_2__ {struct zcrypt_queue* message; } ;
struct zcrypt_queue {TYPE_1__ reply; } ;

/* Variables and functions */
 int /*<<< orphan*/  kfree (struct zcrypt_queue*) ; 

void zcrypt_queue_free(struct zcrypt_queue *zq)
{
	kfree(zq->reply.message);
	kfree(zq);
}