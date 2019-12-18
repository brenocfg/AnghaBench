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
typedef  scalar_t__ LONG ;
typedef  int /*<<< orphan*/  HANDLE ;
typedef  int DWORD ;

/* Variables and functions */
 scalar_t__ ERROR_SUCCESS ; 
 scalar_t__ RegQueryInfoKeyW (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

int GetLongestChildKeyName( HANDLE RegHandle ) {
  LONG Status;
  DWORD MaxAdapterName;

  Status = RegQueryInfoKeyW(RegHandle,
			    NULL,
			    NULL,
			    NULL,
			    NULL,
			    &MaxAdapterName,
			    NULL,
			    NULL,
			    NULL,
			    NULL,
			    NULL,
			    NULL);
  if (Status == ERROR_SUCCESS)
    return MaxAdapterName + 1;
  else
    return -1;
}