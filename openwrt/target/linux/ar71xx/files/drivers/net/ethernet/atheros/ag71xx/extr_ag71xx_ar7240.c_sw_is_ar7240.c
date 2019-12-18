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
struct ar7240sw {scalar_t__ ver; } ;

/* Variables and functions */
 scalar_t__ AR7240_MASK_CTRL_VERSION_AR7240 ; 

__attribute__((used)) static inline int sw_is_ar7240(struct ar7240sw *as)
{
	return as->ver == AR7240_MASK_CTRL_VERSION_AR7240;
}