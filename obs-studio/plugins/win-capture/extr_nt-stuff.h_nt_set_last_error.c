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
typedef  int /*<<< orphan*/  (* RTLNTSTATUSTODOSERRORFUNC ) (int /*<<< orphan*/ ) ;
typedef  int /*<<< orphan*/  NTSTATUS ;

/* Variables and functions */
 int /*<<< orphan*/  SetLastError (int /*<<< orphan*/ ) ; 
 scalar_t__ get_nt_func (char*) ; 

__attribute__((used)) static void nt_set_last_error(NTSTATUS status)
{
	static bool initialized = false;
	static RTLNTSTATUSTODOSERRORFUNC func = NULL;

	if (!initialized) {
		func = (RTLNTSTATUSTODOSERRORFUNC)get_nt_func(
			"RtlNtStatusToDosError");
		initialized = true;
	}

	if (func)
		SetLastError(func(status));
}