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
typedef  enum brcmf_fweh_event_code { ____Placeholder_brcmf_fweh_event_code } brcmf_fweh_event_code ;

/* Variables and functions */

const char *brcmf_fweh_event_name(enum brcmf_fweh_event_code code)
{
	return "nodebug";
}