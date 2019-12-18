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
typedef  int /*<<< orphan*/  WCHAR ;
typedef  int /*<<< orphan*/ * LPWSTR ;

/* Variables and functions */
 int /*<<< orphan*/  CP_ACP ; 
 int MultiByteToWideChar (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char const*,int,int /*<<< orphan*/ *,int) ; 
 scalar_t__ SHAlloc (int) ; 

__attribute__((used)) static __inline LPWSTR __SHCloneStrAtoW(WCHAR **target, const char *source)
{
	int len = MultiByteToWideChar(CP_ACP, 0, source, -1, NULL, 0);
	*target = (WCHAR *)SHAlloc(len * sizeof(WCHAR));
	MultiByteToWideChar(CP_ACP, 0, source, -1, *target, len);
	return *target;
}