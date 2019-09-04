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
typedef  scalar_t__ PFNWGLRELEASEIMAGEBUFFEREVENTSI3DPROC ;
typedef  scalar_t__ PFNWGLDESTROYIMAGEBUFFERI3DPROC ;
typedef  scalar_t__ PFNWGLCREATEIMAGEBUFFERI3DPROC ;
typedef  scalar_t__ PFNWGLASSOCIATEIMAGEBUFFEREVENTSI3DPROC ;
typedef  scalar_t__ (* GLADloadproc ) (char*) ;

/* Variables and functions */
 int /*<<< orphan*/  GLAD_WGL_I3D_image_buffer ; 
 scalar_t__ glad_wglAssociateImageBufferEventsI3D ; 
 scalar_t__ glad_wglCreateImageBufferI3D ; 
 scalar_t__ glad_wglDestroyImageBufferI3D ; 
 scalar_t__ glad_wglReleaseImageBufferEventsI3D ; 

__attribute__((used)) static void load_WGL_I3D_image_buffer(GLADloadproc load) {
	if(!GLAD_WGL_I3D_image_buffer) return;
	glad_wglCreateImageBufferI3D = (PFNWGLCREATEIMAGEBUFFERI3DPROC)load("wglCreateImageBufferI3D");
	glad_wglDestroyImageBufferI3D = (PFNWGLDESTROYIMAGEBUFFERI3DPROC)load("wglDestroyImageBufferI3D");
	glad_wglAssociateImageBufferEventsI3D = (PFNWGLASSOCIATEIMAGEBUFFEREVENTSI3DPROC)load("wglAssociateImageBufferEventsI3D");
	glad_wglReleaseImageBufferEventsI3D = (PFNWGLRELEASEIMAGEBUFFEREVENTSI3DPROC)load("wglReleaseImageBufferEventsI3D");
}