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
 unsigned short C_O_CREAT ; 
 unsigned short C_O_EXCL ; 
 unsigned short C_O_READ ; 
 unsigned short C_O_TRUNC ; 
 unsigned short C_O_WRITE ; 
 unsigned short O_ACCMODE ; 
 unsigned short O_CREAT ; 
 unsigned short O_EXCL ; 
 unsigned short O_RDONLY ; 
 unsigned short O_RDWR ; 
 unsigned short O_TRUNC ; 
 unsigned short O_WRONLY ; 

unsigned short coda_flags_to_cflags(unsigned short flags)
{
	unsigned short coda_flags = 0;
	
	if ((flags & O_ACCMODE) == O_RDONLY)
		coda_flags |= C_O_READ;

	if ((flags & O_ACCMODE) == O_RDWR)
		coda_flags |= C_O_READ | C_O_WRITE;

	if ((flags & O_ACCMODE) == O_WRONLY)
		coda_flags |= C_O_WRITE;

	if (flags & O_TRUNC)
		coda_flags |= C_O_TRUNC;

	if (flags & O_CREAT)
		coda_flags |= C_O_CREAT;

	if (flags & O_EXCL)
		coda_flags |= C_O_EXCL;

	return coda_flags;
}