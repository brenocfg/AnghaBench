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
struct airq_iv {struct airq_iv* avail; struct airq_iv* vector; struct airq_iv* bitlock; struct airq_iv* ptr; struct airq_iv* data; } ;

/* Variables and functions */
 int /*<<< orphan*/  kfree (struct airq_iv*) ; 

void airq_iv_release(struct airq_iv *iv)
{
	kfree(iv->data);
	kfree(iv->ptr);
	kfree(iv->bitlock);
	kfree(iv->vector);
	kfree(iv->avail);
	kfree(iv);
}