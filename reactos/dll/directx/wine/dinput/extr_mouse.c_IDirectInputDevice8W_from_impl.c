#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int /*<<< orphan*/  IDirectInputDevice8W_iface; } ;
struct TYPE_5__ {TYPE_1__ base; } ;
typedef  TYPE_2__ SysMouseImpl ;
typedef  int /*<<< orphan*/  IDirectInputDevice8W ;

/* Variables and functions */

__attribute__((used)) static inline IDirectInputDevice8W *IDirectInputDevice8W_from_impl(SysMouseImpl *This)
{
    return &This->base.IDirectInputDevice8W_iface;
}