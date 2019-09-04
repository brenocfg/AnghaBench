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
 int CEPH_FILE_MODE_RD ; 
 int CEPH_FILE_MODE_RDWR ; 
 int CEPH_FILE_MODE_WR ; 
#define  O_ACCMODE 131 
#define  O_RDONLY 130 
#define  O_RDWR 129 
#define  O_WRONLY 128 

int ceph_flags_to_mode(int flags)
{
	int mode;

#ifdef O_DIRECTORY  /* fixme */
	if ((flags & O_DIRECTORY) == O_DIRECTORY)
		return CEPH_FILE_MODE_PIN;
#endif

	switch (flags & O_ACCMODE) {
	case O_WRONLY:
		mode = CEPH_FILE_MODE_WR;
		break;
	case O_RDONLY:
		mode = CEPH_FILE_MODE_RD;
		break;
	case O_RDWR:
	case O_ACCMODE: /* this is what the VFS does */
		mode = CEPH_FILE_MODE_RDWR;
		break;
	}
#ifdef O_LAZY
	if (flags & O_LAZY)
		mode |= CEPH_FILE_MODE_LAZY;
#endif

	return mode;
}