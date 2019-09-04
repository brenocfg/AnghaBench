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

/* Variables and functions */
 int /*<<< orphan*/  class_unregister (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  uio_class ; 
 int uio_class_registered ; 
 int /*<<< orphan*/  uio_major_cleanup () ; 

__attribute__((used)) static void release_uio_class(void)
{
	uio_class_registered = false;
	class_unregister(&uio_class);
	uio_major_cleanup();
}