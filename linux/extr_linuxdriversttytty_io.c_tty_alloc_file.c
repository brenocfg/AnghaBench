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
struct tty_file_private {int dummy; } ;
struct file {struct tty_file_private* private_data; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 struct tty_file_private* kmalloc (int,int /*<<< orphan*/ ) ; 

int tty_alloc_file(struct file *file)
{
	struct tty_file_private *priv;

	priv = kmalloc(sizeof(*priv), GFP_KERNEL);
	if (!priv)
		return -ENOMEM;

	file->private_data = priv;

	return 0;
}