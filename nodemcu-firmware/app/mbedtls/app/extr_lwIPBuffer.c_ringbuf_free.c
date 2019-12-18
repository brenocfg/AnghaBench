#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  TYPE_1__* ringbuf_t ;
struct TYPE_4__ {struct TYPE_4__* buf; } ;

/* Variables and functions */
 int /*<<< orphan*/  lwIP_ASSERT (int) ; 
 int /*<<< orphan*/  os_free (TYPE_1__*) ; 

void ringbuf_free(ringbuf_t *rb)
{
	lwIP_ASSERT(rb && *rb);
	os_free((*rb)->buf);
	os_free(*rb);
	*rb = NULL;
}