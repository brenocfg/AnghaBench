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
struct platform_device {int dummy; } ;
struct goldfish_pipe_dev {scalar_t__ buffers; int /*<<< orphan*/  pipes; } ;

/* Variables and functions */
 int /*<<< orphan*/  free_page (unsigned long) ; 
 int /*<<< orphan*/  goldfish_pipe_dev ; 
 int /*<<< orphan*/  kfree (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  misc_deregister (int /*<<< orphan*/ *) ; 
 struct goldfish_pipe_dev* pipe_dev ; 

__attribute__((used)) static void goldfish_pipe_device_deinit(struct platform_device *pdev)
{
	struct goldfish_pipe_dev *dev = pipe_dev;

	misc_deregister(&goldfish_pipe_dev);
	kfree(dev->pipes);
	free_page((unsigned long)dev->buffers);
}