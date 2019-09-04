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
struct TYPE_2__ {int proto; } ;

/* Variables and functions */
#define  HV_PROTOCOL_HVSI 129 
#define  HV_PROTOCOL_RAW 128 
 int hvterm_hvsi_get_chars (int /*<<< orphan*/ ,char*,int) ; 
 TYPE_1__** hvterm_privs ; 
 int hvterm_raw_get_chars (int /*<<< orphan*/ ,char*,int) ; 

__attribute__((used)) static int udbg_hvc_getc_poll(void)
{
	int rc = 0;
	char c;

	if (!hvterm_privs[0])
		return -1;

	switch(hvterm_privs[0]->proto) {
	case HV_PROTOCOL_RAW:
		rc = hvterm_raw_get_chars(0, &c, 1);
		break;
	case HV_PROTOCOL_HVSI:
		rc = hvterm_hvsi_get_chars(0, &c, 1);
		break;
	}
	if (!rc)
		return -1;
	return c;
}