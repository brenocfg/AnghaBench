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
typedef  int UINT ;
typedef  int /*<<< orphan*/  HANDLE ;

/* Variables and functions */
 int ARRAYSIZE (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ConStreamGetOSHandle (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * ExtraHandles ; 
 int /*<<< orphan*/  INVALID_HANDLE_VALUE ; 
 int /*<<< orphan*/ * StdStreams ; 

HANDLE GetHandle(UINT Number)
{
    if (Number < 3)
        return ConStreamGetOSHandle(StdStreams[Number]);
        // return GetStdHandle(STD_INPUT_HANDLE - Number);
    else if (Number < ARRAYSIZE(ExtraHandles) + 3)
        return ExtraHandles[Number - 3];
    else
        return INVALID_HANDLE_VALUE;
}