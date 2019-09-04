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

__attribute__((used)) static inline loff_t
s32_to_loff_t(__s32 offset)
{
	return (loff_t)offset;
}