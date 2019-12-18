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
typedef  scalar_t__ PFNWGLENUMGPUSNVPROC ;
typedef  scalar_t__ PFNWGLENUMGPUSFROMAFFINITYDCNVPROC ;
typedef  scalar_t__ PFNWGLENUMGPUDEVICESNVPROC ;
typedef  scalar_t__ PFNWGLDELETEDCNVPROC ;
typedef  scalar_t__ PFNWGLCREATEAFFINITYDCNVPROC ;
typedef  scalar_t__ (* GLADloadproc ) (char*) ;

/* Variables and functions */
 int /*<<< orphan*/  GLAD_WGL_NV_gpu_affinity ; 
 scalar_t__ glad_wglCreateAffinityDCNV ; 
 scalar_t__ glad_wglDeleteDCNV ; 
 scalar_t__ glad_wglEnumGpuDevicesNV ; 
 scalar_t__ glad_wglEnumGpusFromAffinityDCNV ; 
 scalar_t__ glad_wglEnumGpusNV ; 

__attribute__((used)) static void load_WGL_NV_gpu_affinity(GLADloadproc load) {
	if(!GLAD_WGL_NV_gpu_affinity) return;
	glad_wglEnumGpusNV = (PFNWGLENUMGPUSNVPROC)load("wglEnumGpusNV");
	glad_wglEnumGpuDevicesNV = (PFNWGLENUMGPUDEVICESNVPROC)load("wglEnumGpuDevicesNV");
	glad_wglCreateAffinityDCNV = (PFNWGLCREATEAFFINITYDCNVPROC)load("wglCreateAffinityDCNV");
	glad_wglEnumGpusFromAffinityDCNV = (PFNWGLENUMGPUSFROMAFFINITYDCNVPROC)load("wglEnumGpusFromAffinityDCNV");
	glad_wglDeleteDCNV = (PFNWGLDELETEDCNVPROC)load("wglDeleteDCNV");
}