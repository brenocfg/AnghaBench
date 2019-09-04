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
struct dentry {scalar_t__ d_fsdata; } ;

/* Variables and functions */

__attribute__((used)) static inline unsigned long cifs_get_time(struct dentry *dentry)
{
	return (unsigned long) dentry->d_fsdata;
}