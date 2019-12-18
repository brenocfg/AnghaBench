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
struct priv {int /*<<< orphan*/  device; } ;
struct ao {int /*<<< orphan*/  device; struct priv* priv; } ;
typedef  int /*<<< orphan*/  OSStatus ;

/* Variables and functions */
 int /*<<< orphan*/  CHECK_CA_ERROR (char*) ; 
 int /*<<< orphan*/  ca_select_device (struct ao*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static bool reinit_device(struct ao *ao) {
    struct priv *p = ao->priv;

    OSStatus err = ca_select_device(ao, ao->device, &p->device);
    CHECK_CA_ERROR("failed to select device");

    return true;

coreaudio_error:
    return false;
}