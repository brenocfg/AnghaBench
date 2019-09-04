#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct platform_device {int dummy; } ;
struct acer_data {int dummy; } ;
struct TYPE_2__ {struct acer_data data; } ;

/* Variables and functions */
 int /*<<< orphan*/  ACER_CAP_MAILLED ; 
 int /*<<< orphan*/  LED_OFF ; 
 scalar_t__ has_cap (int /*<<< orphan*/ ) ; 
 TYPE_1__* interface ; 
 int /*<<< orphan*/  set_u32 (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void acer_platform_shutdown(struct platform_device *device)
{
	struct acer_data *data = &interface->data;

	if (!data)
		return;

	if (has_cap(ACER_CAP_MAILLED))
		set_u32(LED_OFF, ACER_CAP_MAILLED);
}