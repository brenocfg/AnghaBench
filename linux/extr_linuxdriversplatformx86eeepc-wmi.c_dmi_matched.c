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
struct dmi_system_id {TYPE_1__* matches; int /*<<< orphan*/  driver_data; } ;
struct TYPE_2__ {scalar_t__ substr; } ;

/* Variables and functions */
 int /*<<< orphan*/  et2012_quirks () ; 
 int /*<<< orphan*/  quirks ; 
 scalar_t__ strncmp (char*,char*,int) ; 
 scalar_t__ unlikely (int) ; 

__attribute__((used)) static int dmi_matched(const struct dmi_system_id *dmi)
{
	char *model;

	quirks = dmi->driver_data;

	model = (char *)dmi->matches[1].substr;
	if (unlikely(strncmp(model, "ET2012", 6) == 0))
		et2012_quirks();

	return 1;
}