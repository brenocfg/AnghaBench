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
struct TYPE_2__ {int /*<<< orphan*/  input; } ;

/* Variables and functions */
 int /*<<< orphan*/  SW_LID ; 
 int /*<<< orphan*/  input_report_switch (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  input_sync (int /*<<< orphan*/ ) ; 
 TYPE_1__ s3_wmi ; 
 int s3_wmi_query_lid (int*) ; 

__attribute__((used)) static int s3_wmi_send_lid_state(void)
{
	int ret, lid_sw;

	ret = s3_wmi_query_lid(&lid_sw);
	if (ret)
		return ret;

	input_report_switch(s3_wmi.input, SW_LID, lid_sw);
	input_sync(s3_wmi.input);

	return 0;
}