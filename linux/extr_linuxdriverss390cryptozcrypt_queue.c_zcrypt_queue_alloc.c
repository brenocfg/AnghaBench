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
struct TYPE_2__ {size_t length; int /*<<< orphan*/  message; } ;
struct zcrypt_queue {int /*<<< orphan*/  refcount; int /*<<< orphan*/  list; TYPE_1__ reply; } ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  INIT_LIST_HEAD (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  kfree (struct zcrypt_queue*) ; 
 int /*<<< orphan*/  kmalloc (size_t,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kref_init (int /*<<< orphan*/ *) ; 
 struct zcrypt_queue* kzalloc (int,int /*<<< orphan*/ ) ; 

struct zcrypt_queue *zcrypt_queue_alloc(size_t max_response_size)
{
	struct zcrypt_queue *zq;

	zq = kzalloc(sizeof(struct zcrypt_queue), GFP_KERNEL);
	if (!zq)
		return NULL;
	zq->reply.message = kmalloc(max_response_size, GFP_KERNEL);
	if (!zq->reply.message)
		goto out_free;
	zq->reply.length = max_response_size;
	INIT_LIST_HEAD(&zq->list);
	kref_init(&zq->refcount);
	return zq;

out_free:
	kfree(zq);
	return NULL;
}