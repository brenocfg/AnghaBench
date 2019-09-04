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
struct file {struct ca8210_priv* private_data; } ;
struct ca8210_priv {int /*<<< orphan*/  spi; } ;

/* Variables and functions */
#define  CA8210_IOCTL_HARD_RESET 128 
 int /*<<< orphan*/  ca8210_reset_send (int /*<<< orphan*/ ,unsigned long) ; 

__attribute__((used)) static long ca8210_test_int_ioctl(
	struct file *filp,
	unsigned int ioctl_num,
	unsigned long ioctl_param
)
{
	struct ca8210_priv *priv = filp->private_data;

	switch (ioctl_num) {
	case CA8210_IOCTL_HARD_RESET:
		ca8210_reset_send(priv->spi, ioctl_param);
		break;
	default:
		break;
	}
	return 0;
}