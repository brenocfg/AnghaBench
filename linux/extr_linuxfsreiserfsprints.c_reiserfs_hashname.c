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
 int R5_HASH ; 
 int TEA_HASH ; 
 int YURA_HASH ; 

char *reiserfs_hashname(int code)
{
	if (code == YURA_HASH)
		return "rupasov";
	if (code == TEA_HASH)
		return "tea";
	if (code == R5_HASH)
		return "r5";

	return "unknown";
}