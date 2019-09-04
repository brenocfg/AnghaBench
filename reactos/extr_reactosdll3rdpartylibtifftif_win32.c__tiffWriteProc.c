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
typedef  int /*<<< orphan*/  uint8 ;
typedef  scalar_t__ uint64 ;
typedef  scalar_t__ tmsize_t ;
typedef  int /*<<< orphan*/  thandle_t ;
typedef  int /*<<< orphan*/  LPVOID ;
typedef  int DWORD ;

/* Variables and functions */
 int /*<<< orphan*/  WriteFile (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static tmsize_t
_tiffWriteProc(thandle_t fd, void* buf, tmsize_t size)
{
	/* tmsize_t is 64bit on 64bit systems, but the WinAPI WriteFile takes
	 * 32bit sizes, so we loop through the data in suitable 32bit sized
	 * chunks */
	uint8* ma;
	uint64 mb;
	DWORD n;
	DWORD o;
	tmsize_t p;
	ma=(uint8*)buf;
	mb=size;
	p=0;
	while (mb>0)
	{
		n=0x80000000UL;
		if ((uint64)n>mb)
			n=(DWORD)mb;
		if (!WriteFile(fd,(LPVOID)ma,n,&o,NULL))
			return(0);
		ma+=o;
		mb-=o;
		p+=o;
		if (o!=n)
			break;
	}
	return(p);
}