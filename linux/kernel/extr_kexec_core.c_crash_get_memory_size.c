#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {scalar_t__ end; scalar_t__ start; } ;

/* Variables and functions */
 TYPE_1__ crashk_res ; 
 int /*<<< orphan*/  kexec_mutex ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 size_t resource_size (TYPE_1__*) ; 

size_t crash_get_memory_size(void)
{
	size_t size = 0;

	mutex_lock(&kexec_mutex);
	if (crashk_res.end != crashk_res.start)
		size = resource_size(&crashk_res);
	mutex_unlock(&kexec_mutex);
	return size;
}