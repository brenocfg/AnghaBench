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
struct usbatm_data {int /*<<< orphan*/  refcount; } ;

/* Variables and functions */
 int /*<<< orphan*/  kref_get (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void usbatm_get_instance(struct usbatm_data *instance)
{
	kref_get(&instance->refcount);
}