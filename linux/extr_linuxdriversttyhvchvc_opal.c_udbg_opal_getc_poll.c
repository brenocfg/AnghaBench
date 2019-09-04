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
 TYPE_1__ hvc_opal_boot_priv ; 
 unsigned int hvc_opal_boot_termno ; 
 int hvc_opal_hvsi_get_chars (unsigned int,char*,int) ; 
 int opal_get_chars (unsigned int,char*,int) ; 

__attribute__((used)) static int udbg_opal_getc_poll(void)
{
	unsigned int termno = hvc_opal_boot_termno;
	int rc = 0;
	char c;

	switch(hvc_opal_boot_priv.proto) {
	case HV_PROTOCOL_RAW:
		rc = opal_get_chars(termno, &c, 1);
		break;
	case HV_PROTOCOL_HVSI:
		rc = hvc_opal_hvsi_get_chars(termno, &c, 1);
		break;
	}
	if (!rc)
		return -1;
	return c;
}