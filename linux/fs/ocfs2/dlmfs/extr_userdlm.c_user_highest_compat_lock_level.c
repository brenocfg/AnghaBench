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
 int DLM_LOCK_EX ; 
 int DLM_LOCK_NL ; 
 int DLM_LOCK_PR ; 

__attribute__((used)) static inline int user_highest_compat_lock_level(int level)
{
	int new_level = DLM_LOCK_EX;

	if (level == DLM_LOCK_EX)
		new_level = DLM_LOCK_NL;
	else if (level == DLM_LOCK_PR)
		new_level = DLM_LOCK_PR;
	return new_level;
}