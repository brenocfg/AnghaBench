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
#define  NF_ACCEPT 130 
#define  NF_DROP 129 
#define  NF_QUEUE 128 
 int XT_RETURN ; 

__attribute__((used)) static bool verdict_ok(int verdict)
{
	if (verdict > 0)
		return true;

	if (verdict < 0) {
		int v = -verdict - 1;

		if (verdict == XT_RETURN)
			return true;

		switch (v) {
		case NF_ACCEPT: return true;
		case NF_DROP: return true;
		case NF_QUEUE: return true;
		default:
			break;
		}

		return false;
	}

	return false;
}