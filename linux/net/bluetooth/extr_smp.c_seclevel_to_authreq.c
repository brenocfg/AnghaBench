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
typedef  int __u8 ;

/* Variables and functions */
#define  BT_SECURITY_FIPS 130 
#define  BT_SECURITY_HIGH 129 
#define  BT_SECURITY_MEDIUM 128 
 int SMP_AUTH_BONDING ; 
 int SMP_AUTH_MITM ; 
 int SMP_AUTH_NONE ; 

__attribute__((used)) static __u8 seclevel_to_authreq(__u8 sec_level)
{
	switch (sec_level) {
	case BT_SECURITY_FIPS:
	case BT_SECURITY_HIGH:
		return SMP_AUTH_MITM | SMP_AUTH_BONDING;
	case BT_SECURITY_MEDIUM:
		return SMP_AUTH_BONDING;
	default:
		return SMP_AUTH_NONE;
	}
}