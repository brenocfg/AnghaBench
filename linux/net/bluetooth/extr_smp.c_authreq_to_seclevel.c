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
typedef  int u8 ;

/* Variables and functions */
 int BT_SECURITY_FIPS ; 
 int BT_SECURITY_HIGH ; 
 int BT_SECURITY_MEDIUM ; 
 int SMP_AUTH_MITM ; 
 int SMP_AUTH_SC ; 

__attribute__((used)) static u8 authreq_to_seclevel(u8 authreq)
{
	if (authreq & SMP_AUTH_MITM) {
		if (authreq & SMP_AUTH_SC)
			return BT_SECURITY_FIPS;
		else
			return BT_SECURITY_HIGH;
	} else {
		return BT_SECURITY_MEDIUM;
	}
}