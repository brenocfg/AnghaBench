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
 int FD_SETSIZE ; 
 int getdtablesize () ; 

int
_rpc_dtablesize(void)
{
#ifdef _WIN32
	return FD_SETSIZE;
#else
	static int size;

	if (size == 0) {
		size = getdtablesize();
		if (size > FD_SETSIZE)
			size = FD_SETSIZE;
	}
	return (size);
#endif
}