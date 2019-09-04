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
struct bcm2835_audio_instance {int /*<<< orphan*/  vchi_mutex; int /*<<< orphan*/  vchi_handle; } ;

/* Variables and functions */
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vchi_service_release (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void bcm2835_audio_unlock(struct bcm2835_audio_instance *instance)
{
	vchi_service_release(instance->vchi_handle);
	mutex_unlock(&instance->vchi_mutex);
}