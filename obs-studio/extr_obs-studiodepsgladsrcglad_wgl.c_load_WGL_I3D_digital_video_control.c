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
typedef  scalar_t__ PFNWGLSETDIGITALVIDEOPARAMETERSI3DPROC ;
typedef  scalar_t__ PFNWGLGETDIGITALVIDEOPARAMETERSI3DPROC ;
typedef  scalar_t__ (* GLADloadproc ) (char*) ;

/* Variables and functions */
 int /*<<< orphan*/  GLAD_WGL_I3D_digital_video_control ; 
 scalar_t__ glad_wglGetDigitalVideoParametersI3D ; 
 scalar_t__ glad_wglSetDigitalVideoParametersI3D ; 

__attribute__((used)) static void load_WGL_I3D_digital_video_control(GLADloadproc load) {
	if(!GLAD_WGL_I3D_digital_video_control) return;
	glad_wglGetDigitalVideoParametersI3D = (PFNWGLGETDIGITALVIDEOPARAMETERSI3DPROC)load("wglGetDigitalVideoParametersI3D");
	glad_wglSetDigitalVideoParametersI3D = (PFNWGLSETDIGITALVIDEOPARAMETERSI3DPROC)load("wglSetDigitalVideoParametersI3D");
}