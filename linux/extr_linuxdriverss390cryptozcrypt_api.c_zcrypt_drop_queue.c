#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct zcrypt_queue {TYPE_4__* queue; int /*<<< orphan*/  load; int /*<<< orphan*/  request_count; } ;
struct zcrypt_card {int /*<<< orphan*/  load; } ;
struct module {int dummy; } ;
struct TYPE_7__ {int /*<<< orphan*/  device; TYPE_2__* drv; } ;
struct TYPE_8__ {TYPE_3__ ap_dev; } ;
struct TYPE_5__ {struct module* owner; } ;
struct TYPE_6__ {TYPE_1__ driver; } ;

/* Variables and functions */
 int /*<<< orphan*/  atomic_sub (unsigned int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  module_put (struct module*) ; 
 int /*<<< orphan*/  put_device (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  zcrypt_queue_put (struct zcrypt_queue*) ; 

__attribute__((used)) static inline void zcrypt_drop_queue(struct zcrypt_card *zc,
				     struct zcrypt_queue *zq,
				     unsigned int weight)
{
	struct module *mod = zq->queue->ap_dev.drv->driver.owner;

	zq->request_count--;
	atomic_sub(weight, &zc->load);
	atomic_sub(weight, &zq->load);
	put_device(&zq->queue->ap_dev.device);
	zcrypt_queue_put(zq);
	module_put(mod);
}