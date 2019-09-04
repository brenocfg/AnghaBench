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
typedef  int /*<<< orphan*/  loff_t ;
typedef  int /*<<< orphan*/  __s32 ;

/* Variables and functions */
 int /*<<< orphan*/  NLM_OFFSET_MAX ; 

__attribute__((used)) static inline __s32
loff_t_to_s32(loff_t offset)
{
	__s32 res;
	if (offset >= NLM_OFFSET_MAX)
		res = NLM_OFFSET_MAX;
	else if (offset <= -NLM_OFFSET_MAX)
		res = -NLM_OFFSET_MAX;
	else
		res = offset;
	return res;
}