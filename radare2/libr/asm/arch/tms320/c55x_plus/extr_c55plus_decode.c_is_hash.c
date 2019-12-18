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
typedef  int st32 ;

/* Variables and functions */

__attribute__((used)) static bool is_hash(st32 hash_code)
{
	bool ret;

	switch(hash_code) {
		case 0xE8:
		case 0xE9:
		case 0xEA:
		case 0xEC:
		case 0x1A8:
		case 0x1DC:
		case 0x1E1:
		case 0x1E2:
		case 0x1E3:
		case 0x1E4:
			ret = 1;
			break;
		default:
		ret = 0;
	}

	return ret;
}