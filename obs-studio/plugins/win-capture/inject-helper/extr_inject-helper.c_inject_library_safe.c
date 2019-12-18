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
typedef  int /*<<< orphan*/  wchar_t ;
typedef  int /*<<< orphan*/  DWORD ;

/* Variables and functions */
 int inject_library_safe_obf (int /*<<< orphan*/ ,int /*<<< orphan*/  const*,char*,int) ; 

__attribute__((used)) static inline int inject_library_safe(DWORD thread_id, const wchar_t *dll)
{
	return inject_library_safe_obf(thread_id, dll, "[bs^fbkmwuKfmfOvI",
				       0xEAD293602FCF9778ULL);
}