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
typedef  scalar_t__ uint64 ;
typedef  int /*<<< orphan*/  thandle_t ;
struct TYPE_2__ {scalar_t__ LowPart; scalar_t__ QuadPart; int /*<<< orphan*/  HighPart; } ;
typedef  TYPE_1__ LARGE_INTEGER ;
typedef  int /*<<< orphan*/  DWORD ;

/* Variables and functions */
 int /*<<< orphan*/  FILE_BEGIN ; 
 int /*<<< orphan*/  FILE_CURRENT ; 
 int /*<<< orphan*/  FILE_END ; 
 scalar_t__ GetLastError () ; 
 scalar_t__ INVALID_SET_FILE_POINTER ; 
 scalar_t__ NO_ERROR ; 
#define  SEEK_CUR 130 
#define  SEEK_END 129 
#define  SEEK_SET 128 
 scalar_t__ SetFilePointer (int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static uint64
_tiffSeekProc(thandle_t fd, uint64 off, int whence)
{
	LARGE_INTEGER offli;
	DWORD dwMoveMethod;
	offli.QuadPart = off;
	switch(whence)
	{
		case SEEK_SET:
			dwMoveMethod = FILE_BEGIN;
			break;
		case SEEK_CUR:
			dwMoveMethod = FILE_CURRENT;
			break;
		case SEEK_END:
			dwMoveMethod = FILE_END;
			break;
		default:
			dwMoveMethod = FILE_BEGIN;
			break;
	}
	offli.LowPart=SetFilePointer(fd,offli.LowPart,&offli.HighPart,dwMoveMethod);
	if ((offli.LowPart==INVALID_SET_FILE_POINTER)&&(GetLastError()!=NO_ERROR))
		offli.QuadPart=0;
	return(offli.QuadPart);
}