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
struct bcm2835_audio_instance {int /*<<< orphan*/  vchi_handle; int /*<<< orphan*/  vchi_mutex; } ;

/* Variables and functions */
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vchi_service_use (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void bcm2835_audio_lock(struct bcm2835_audio_instance *instance)
{
	mutex_lock(&instance->vchi_mutex);
	vchi_service_use(instance->vchi_handle);
}