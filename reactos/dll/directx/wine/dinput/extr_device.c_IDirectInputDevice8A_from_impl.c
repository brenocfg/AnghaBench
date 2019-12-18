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
struct TYPE_3__ {int /*<<< orphan*/  IDirectInputDevice8A_iface; } ;
typedef  TYPE_1__ IDirectInputDeviceImpl ;
typedef  int /*<<< orphan*/  IDirectInputDevice8A ;

/* Variables and functions */

__attribute__((used)) static inline IDirectInputDevice8A *IDirectInputDevice8A_from_impl(IDirectInputDeviceImpl *This)
{
    return &This->IDirectInputDevice8A_iface;
}