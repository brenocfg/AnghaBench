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
typedef  int umode_t ;

/* Variables and functions */
 int EINVAL ; 
 int EPERM ; 
#define  S_IFBLK 133 
#define  S_IFCHR 132 
#define  S_IFDIR 131 
#define  S_IFIFO 130 
 int S_IFMT ; 
#define  S_IFREG 129 
#define  S_IFSOCK 128 

__attribute__((used)) static int may_mknod(umode_t mode)
{
	switch (mode & S_IFMT) {
	case S_IFREG:
	case S_IFCHR:
	case S_IFBLK:
	case S_IFIFO:
	case S_IFSOCK:
	case 0: /* zero mode translates to S_IFREG */
		return 0;
	case S_IFDIR:
		return -EPERM;
	default:
		return -EINVAL;
	}
}