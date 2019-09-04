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
struct nvmem_device {int (* reg_read ) (int /*<<< orphan*/ ,unsigned int,void*,size_t) ;int /*<<< orphan*/  priv; } ;

/* Variables and functions */
 int EINVAL ; 
 int stub1 (int /*<<< orphan*/ ,unsigned int,void*,size_t) ; 

__attribute__((used)) static int nvmem_reg_read(struct nvmem_device *nvmem, unsigned int offset,
			  void *val, size_t bytes)
{
	if (nvmem->reg_read)
		return nvmem->reg_read(nvmem->priv, offset, val, bytes);

	return -EINVAL;
}