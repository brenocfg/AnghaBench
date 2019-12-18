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
struct configfs_dirent {int s_mode; } ;

/* Variables and functions */

__attribute__((used)) static inline unsigned char dt_type(struct configfs_dirent *sd)
{
	return (sd->s_mode >> 12) & 15;
}