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
typedef  int /*<<< orphan*/  ULONG ;
typedef  int /*<<< orphan*/  SYSTEM_INFORMATION_CLASS ;
typedef  int /*<<< orphan*/  PVOID ;
typedef  int /*<<< orphan*/  PULONG ;
typedef  int /*<<< orphan*/  NTSTATUS ;
typedef  int /*<<< orphan*/  (* NTQUERYSYSTEMINFORMATIONFUNC ) (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ;

/* Variables and functions */
 scalar_t__ get_nt_func (char*) ; 

__attribute__((used)) static NTSTATUS nt_query_information(SYSTEM_INFORMATION_CLASS info_class,
				     PVOID info, ULONG info_len, PULONG ret_len)
{
	static bool initialized = false;
	static NTQUERYSYSTEMINFORMATIONFUNC func = NULL;

	if (!initialized) {
		func = (NTQUERYSYSTEMINFORMATIONFUNC)get_nt_func(
			"NtQuerySystemInformation");
		initialized = true;
	}

	if (func)
		return func(info_class, info, info_len, ret_len);
	return (NTSTATUS)-1;
}