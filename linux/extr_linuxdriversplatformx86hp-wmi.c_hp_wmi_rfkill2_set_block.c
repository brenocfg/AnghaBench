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
typedef  int /*<<< orphan*/  buffer ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  HPWMI_WIRELESS2_QUERY ; 
 int /*<<< orphan*/  HPWMI_WRITE ; 
 int hp_wmi_perform_query (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int hp_wmi_rfkill2_set_block(void *data, bool blocked)
{
	int rfkill_id = (int)(long)data;
	char buffer[4] = { 0x01, 0x00, rfkill_id, !blocked };
	int ret;

	ret = hp_wmi_perform_query(HPWMI_WIRELESS2_QUERY, HPWMI_WRITE,
				   buffer, sizeof(buffer), 0);

	return ret <= 0 ? ret : -EINVAL;
}