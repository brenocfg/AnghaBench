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
 int OVL_XINO_AUTO ; 
 int OVL_XINO_OFF ; 
 scalar_t__ ovl_xino_auto_def ; 

__attribute__((used)) static inline int ovl_xino_def(void)
{
	return ovl_xino_auto_def ? OVL_XINO_AUTO : OVL_XINO_OFF;
}