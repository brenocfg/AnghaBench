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
typedef  int /*<<< orphan*/  TCHAR ;
typedef  int /*<<< orphan*/  FRESULT ;
typedef  scalar_t__ BYTE ;

/* Variables and functions */
 scalar_t__ CurrVol ; 
 int /*<<< orphan*/  FR_INVALID_DRIVE ; 
 int /*<<< orphan*/  FR_OK ; 
 int get_ldnumber (int /*<<< orphan*/  const**) ; 

FRESULT f_chdrive (
	const TCHAR* path		/* Drive number to set */
)
{
	int vol;


	/* Get logical drive number */
	vol = get_ldnumber(&path);
	if (vol < 0) return FR_INVALID_DRIVE;
	CurrVol = (BYTE)vol;	/* Set it as current volume */

	return FR_OK;
}