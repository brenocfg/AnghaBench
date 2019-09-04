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
typedef  int /*<<< orphan*/  HMODULE ;
typedef  int /*<<< orphan*/  GLubyte ;

/* Variables and functions */
 int /*<<< orphan*/  GetModuleHandle (char*) ; 
 void* GetProcAddress (int /*<<< orphan*/ ,int /*<<< orphan*/  const*) ; 
 void* wglGetProcAddress (int /*<<< orphan*/  const*) ; 

__attribute__((used)) static void *wglgpa(const GLubyte *procName)
{
    HMODULE oglmod;
    void *res = wglGetProcAddress(procName);
    if (res)
        return res;
    oglmod = GetModuleHandle(L"opengl32.dll");
    return GetProcAddress(oglmod, procName);
}