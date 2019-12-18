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
struct dentry {int dummy; } ;

/* Variables and functions */
 char* __dentry_path (struct dentry*,char*,int) ; 

char *dentry_path_raw(struct dentry *dentry, char *buf, int buflen)
{
	return __dentry_path(dentry, buf, buflen);
}