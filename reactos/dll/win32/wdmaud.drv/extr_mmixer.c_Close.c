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
typedef  int /*<<< orphan*/  MIXER_STATUS ;
typedef  int /*<<< orphan*/  HANDLE ;

/* Variables and functions */
 scalar_t__ CloseHandle (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MM_STATUS_SUCCESS ; 
 int /*<<< orphan*/  MM_STATUS_UNSUCCESSFUL ; 

MIXER_STATUS
Close(HANDLE hDevice)
{
    if (CloseHandle(hDevice))
        return MM_STATUS_SUCCESS;
    else
        return MM_STATUS_UNSUCCESSFUL;
}