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
 int /*<<< orphan*/  INT_MAX ; 
 int rm_rf_depth_pat (char const*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

int rm_rf(const char *path)
{
	return rm_rf_depth_pat(path, INT_MAX, NULL);
}