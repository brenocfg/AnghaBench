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

/* Variables and functions */
 scalar_t__ GetProcAddress (void*,char*) ; 
 void* LoadLibrary (char*) ; 
 void* d3d11_D3D11CreateDevice ; 
 void* d3d11_dll ; 
 void* d3d9_dll ; 
 void* dxva2_dll ; 

__attribute__((used)) static void d3d_do_load(void)
{
    d3d11_dll = LoadLibrary(L"d3d11.dll");
    d3d9_dll  = LoadLibrary(L"d3d9.dll");
    dxva2_dll = LoadLibrary(L"dxva2.dll");

    if (d3d11_dll) {
        d3d11_D3D11CreateDevice =
            (void *)GetProcAddress(d3d11_dll, "D3D11CreateDevice");
    }
}