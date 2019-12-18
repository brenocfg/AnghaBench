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
struct vfs_cap_data {int dummy; } ;

/* Variables and functions */
 scalar_t__ is_v2header (size_t,struct vfs_cap_data const*) ; 
 scalar_t__ is_v3header (size_t,struct vfs_cap_data const*) ; 

__attribute__((used)) static bool validheader(size_t size, const struct vfs_cap_data *cap)
{
	return is_v2header(size, cap) || is_v3header(size, cap);
}