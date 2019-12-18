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

/* Variables and functions */
#define  WSC_SECURITY_PROVIDER_ANTISPYWARE 130 
#define  WSC_SECURITY_PROVIDER_ANTIVIRUS 129 
#define  WSC_SECURITY_PROVIDER_FIREWALL 128 

__attribute__((used)) static const char *get_str_for_type(int type)
{
	switch (type) {
	case WSC_SECURITY_PROVIDER_ANTIVIRUS:
		return "AV";
	case WSC_SECURITY_PROVIDER_FIREWALL:
		return "FW";
	case WSC_SECURITY_PROVIDER_ANTISPYWARE:
		return "ASW";
	default:
		return "unknown";
	}
}