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
struct socket {int dummy; } ;
struct tap_queue {struct socket sock; } ;
struct file {struct tap_queue* private_data; int /*<<< orphan*/ * f_op; } ;

/* Variables and functions */
 int /*<<< orphan*/  EBADFD ; 
 int /*<<< orphan*/  EINVAL ; 
 struct socket* ERR_PTR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tap_fops ; 

struct socket *tap_get_socket(struct file *file)
{
	struct tap_queue *q;
	if (file->f_op != &tap_fops)
		return ERR_PTR(-EINVAL);
	q = file->private_data;
	if (!q)
		return ERR_PTR(-EBADFD);
	return &q->sock;
}