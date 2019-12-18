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
typedef  int /*<<< orphan*/  HRSRC ;
typedef  int /*<<< orphan*/  HRESULT ;
typedef  int /*<<< orphan*/  HMODULE ;
typedef  int /*<<< orphan*/  HGLOBAL ;
typedef  scalar_t__ DWORD ;

/* Variables and functions */
 int /*<<< orphan*/  GetLastError () ; 
 int /*<<< orphan*/  HRESULT_FROM_WIN32 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  LoadResource (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 void* LockResource (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  S_OK ; 
 scalar_t__ SizeofResource (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

HRESULT load_resource_into_memory(HMODULE module, HRSRC resinfo, void **buffer, DWORD *length)
{
    HGLOBAL resource;

    *length = SizeofResource(module, resinfo);
    if(*length == 0) return HRESULT_FROM_WIN32(GetLastError());

    resource = LoadResource(module, resinfo);
    if( !resource ) return HRESULT_FROM_WIN32(GetLastError());

    *buffer = LockResource(resource);
    if(*buffer == NULL) return HRESULT_FROM_WIN32(GetLastError());

    return S_OK;
}