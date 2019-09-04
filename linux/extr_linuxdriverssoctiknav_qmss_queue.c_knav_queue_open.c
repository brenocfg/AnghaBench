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
typedef  void knav_queue ;

/* Variables and functions */
 int /*<<< orphan*/  EINVAL ; 
 void* ERR_PTR (int /*<<< orphan*/ ) ; 
#define  KNAV_QUEUE_ACC 130 
#define  KNAV_QUEUE_GP 129 
#define  KNAV_QUEUE_QPEND 128 
 void* knav_queue_open_by_id (char const*,unsigned int,unsigned int) ; 
 void* knav_queue_open_by_type (char const*,unsigned int,unsigned int) ; 

void *knav_queue_open(const char *name, unsigned id,
					unsigned flags)
{
	struct knav_queue *qh = ERR_PTR(-EINVAL);

	switch (id) {
	case KNAV_QUEUE_QPEND:
	case KNAV_QUEUE_ACC:
	case KNAV_QUEUE_GP:
		qh = knav_queue_open_by_type(name, id, flags);
		break;

	default:
		qh = knav_queue_open_by_id(name, id, flags);
		break;
	}
	return qh;
}