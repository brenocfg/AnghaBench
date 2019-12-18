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
typedef  scalar_t__ WPARAM ;
typedef  int /*<<< orphan*/  RDebug ;
typedef  int /*<<< orphan*/  PVOID ;
typedef  int /*<<< orphan*/  HANDLE ;

/* Variables and functions */
 int /*<<< orphan*/  GetHeapGlobalsOffset (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ReadProcessMemory (int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__*,int,int /*<<< orphan*/ *) ; 
 scalar_t__ RtlpHpHeapGlobalsOffset ; 
 scalar_t__ RtlpLFHKeyOffset ; 
 int /*<<< orphan*/  eprintf (char*) ; 
 int /*<<< orphan*/  r_return_val_if_fail (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  r_sys_perror (char*) ; 

__attribute__((used)) static bool GetLFHKey(RDebug *dbg, HANDLE h_proc, bool segment, WPARAM *lfhKey) {
	r_return_val_if_fail (dbg, 0);
	WPARAM lfhKeyLocation;

	if (!GetHeapGlobalsOffset (dbg, h_proc)) {
		*lfhKey = 0;
		return false;
	}

	if (segment) {
		lfhKeyLocation = RtlpHpHeapGlobalsOffset + sizeof (WPARAM);
	} else {
		lfhKeyLocation = RtlpLFHKeyOffset; // ntdll!RtlpLFHKey
	}
	if (!ReadProcessMemory (h_proc, (PVOID)lfhKeyLocation, lfhKey, sizeof (WPARAM), NULL)) {
		r_sys_perror ("ReadProcessMemory");
		eprintf ("LFH key not found.\n");
		*lfhKey = 0;
		return false;
	}
	return true;
}