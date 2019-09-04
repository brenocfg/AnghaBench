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
typedef  unsigned int u8 ;

/* Variables and functions */
 int EINVAL ; 
#define  KG_USAGE_SEAL 129 
#define  KG_USAGE_SIGN 128 

__attribute__((used)) static int
arcfour_hmac_md5_usage_to_salt(unsigned int usage, u8 salt[4])
{
	unsigned int ms_usage;

	switch (usage) {
	case KG_USAGE_SIGN:
		ms_usage = 15;
		break;
	case KG_USAGE_SEAL:
		ms_usage = 13;
		break;
	default:
		return -EINVAL;
	}
	salt[0] = (ms_usage >> 0) & 0xff;
	salt[1] = (ms_usage >> 8) & 0xff;
	salt[2] = (ms_usage >> 16) & 0xff;
	salt[3] = (ms_usage >> 24) & 0xff;

	return 0;
}