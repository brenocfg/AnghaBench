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
struct TYPE_2__ {size_t count; int /*<<< orphan*/  cda; } ;
struct raw3270_request {TYPE_1__ ccw; } ;

/* Variables and functions */
 int /*<<< orphan*/  __pa (void*) ; 

void
raw3270_request_set_data(struct raw3270_request *rq, void *data, size_t size)
{
	rq->ccw.cda = __pa(data);
	rq->ccw.count = size;
}