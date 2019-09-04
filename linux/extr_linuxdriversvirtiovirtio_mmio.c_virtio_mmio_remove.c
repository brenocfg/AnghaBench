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
struct virtio_mmio_device {int /*<<< orphan*/  vdev; } ;
struct platform_device {int dummy; } ;

/* Variables and functions */
 struct virtio_mmio_device* platform_get_drvdata (struct platform_device*) ; 
 int /*<<< orphan*/  unregister_virtio_device (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int virtio_mmio_remove(struct platform_device *pdev)
{
	struct virtio_mmio_device *vm_dev = platform_get_drvdata(pdev);
	unregister_virtio_device(&vm_dev->vdev);

	return 0;
}