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
struct inode {struct ca8210_priv* i_private; } ;
struct file {struct ca8210_priv* private_data; } ;
struct ca8210_priv {int dummy; } ;

/* Variables and functions */

__attribute__((used)) static int ca8210_test_int_open(struct inode *inodp, struct file *filp)
{
	struct ca8210_priv *priv = inodp->i_private;

	filp->private_data = priv;
	return 0;
}