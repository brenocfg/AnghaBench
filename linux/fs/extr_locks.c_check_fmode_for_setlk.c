#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct file_lock {int fl_type; TYPE_1__* fl_file; } ;
struct TYPE_2__ {int f_mode; } ;

/* Variables and functions */
 int EBADF ; 
 int FMODE_READ ; 
 int FMODE_WRITE ; 
#define  F_RDLCK 129 
#define  F_WRLCK 128 

__attribute__((used)) static int
check_fmode_for_setlk(struct file_lock *fl)
{
	switch (fl->fl_type) {
	case F_RDLCK:
		if (!(fl->fl_file->f_mode & FMODE_READ))
			return -EBADF;
		break;
	case F_WRLCK:
		if (!(fl->fl_file->f_mode & FMODE_WRITE))
			return -EBADF;
	}
	return 0;
}