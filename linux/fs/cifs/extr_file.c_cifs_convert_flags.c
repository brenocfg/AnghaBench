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
 int FILE_APPEND_DATA ; 
 int FILE_READ_ATTRIBUTES ; 
 int FILE_READ_DATA ; 
 int FILE_WRITE_ATTRIBUTES ; 
 int FILE_WRITE_DATA ; 
 int FILE_WRITE_EA ; 
 int GENERIC_READ ; 
 int GENERIC_WRITE ; 
 unsigned int O_ACCMODE ; 
 unsigned int O_RDONLY ; 
 unsigned int O_RDWR ; 
 unsigned int O_WRONLY ; 
 int READ_CONTROL ; 

__attribute__((used)) static inline int cifs_convert_flags(unsigned int flags)
{
	if ((flags & O_ACCMODE) == O_RDONLY)
		return GENERIC_READ;
	else if ((flags & O_ACCMODE) == O_WRONLY)
		return GENERIC_WRITE;
	else if ((flags & O_ACCMODE) == O_RDWR) {
		/* GENERIC_ALL is too much permission to request
		   can cause unnecessary access denied on create */
		/* return GENERIC_ALL; */
		return (GENERIC_READ | GENERIC_WRITE);
	}

	return (READ_CONTROL | FILE_WRITE_ATTRIBUTES | FILE_READ_ATTRIBUTES |
		FILE_WRITE_EA | FILE_APPEND_DATA | FILE_WRITE_DATA |
		FILE_READ_DATA);
}