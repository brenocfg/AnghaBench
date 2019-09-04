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
typedef  scalar_t__ u32 ;
struct tsi721_device {scalar_t__ regs; } ;
struct rio_mport {struct tsi721_device* priv; } ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  iowrite32 (scalar_t__,scalar_t__) ; 

__attribute__((used)) static int tsi721_lcwrite(struct rio_mport *mport, int index, u32 offset,
			  int len, u32 data)
{
	struct tsi721_device *priv = mport->priv;

	if (len != sizeof(u32))
		return -EINVAL; /* only 32-bit access is supported */

	iowrite32(data, priv->regs + offset);

	return 0;
}