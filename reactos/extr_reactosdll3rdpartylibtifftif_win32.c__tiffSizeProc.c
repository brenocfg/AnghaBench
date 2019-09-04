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
typedef  int /*<<< orphan*/  uint64 ;
typedef  int /*<<< orphan*/  thandle_t ;
struct TYPE_2__ {int /*<<< orphan*/  QuadPart; int /*<<< orphan*/  HighPart; int /*<<< orphan*/  LowPart; } ;
typedef  TYPE_1__ ULARGE_INTEGER ;

/* Variables and functions */
 int /*<<< orphan*/  GetFileSize (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static uint64
_tiffSizeProc(thandle_t fd)
{
	ULARGE_INTEGER m;
	m.LowPart=GetFileSize(fd,&m.HighPart);
	return(m.QuadPart);
}