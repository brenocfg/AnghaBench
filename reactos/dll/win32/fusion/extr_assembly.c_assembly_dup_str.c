#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  WCHAR ;
struct TYPE_3__ {int /*<<< orphan*/ * strings; } ;
typedef  int /*<<< orphan*/ * LPWSTR ;
typedef  int /*<<< orphan*/  LPCSTR ;
typedef  size_t DWORD ;
typedef  TYPE_1__ ASSEMBLY ;

/* Variables and functions */
 int /*<<< orphan*/  CP_ACP ; 
 int MultiByteToWideChar (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/ * heap_alloc (int) ; 

__attribute__((used)) static LPWSTR assembly_dup_str(const ASSEMBLY *assembly, DWORD index)
{
    int len;
    LPWSTR cpy;
    LPCSTR str = (LPCSTR)&assembly->strings[index];

    len = MultiByteToWideChar(CP_ACP, 0, str, -1, NULL, 0);

    if ((cpy = heap_alloc(len * sizeof(WCHAR))))
        MultiByteToWideChar(CP_ACP, 0, str, -1, cpy, len);

    return cpy;
}