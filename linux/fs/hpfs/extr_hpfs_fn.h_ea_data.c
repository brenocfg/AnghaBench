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
struct extended_attribute {int namelen; } ;

/* Variables and functions */

__attribute__((used)) static inline char *ea_data(struct extended_attribute *ea)
{
	return (char *)((char *)ea + 5 + ea->namelen);
}