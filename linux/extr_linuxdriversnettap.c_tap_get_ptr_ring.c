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
struct ptr_ring {int dummy; } ;
struct tap_queue {struct ptr_ring ring; } ;
struct file {struct tap_queue* private_data; int /*<<< orphan*/ * f_op; } ;

/* Variables and functions */
 int /*<<< orphan*/  EBADFD ; 
 int /*<<< orphan*/  EINVAL ; 
 struct ptr_ring* ERR_PTR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tap_fops ; 

struct ptr_ring *tap_get_ptr_ring(struct file *file)
{
	struct tap_queue *q;

	if (file->f_op != &tap_fops)
		return ERR_PTR(-EINVAL);
	q = file->private_data;
	if (!q)
		return ERR_PTR(-EBADFD);
	return &q->ring;
}