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
typedef  scalar_t__ PFNGLXDESTROYGLXVIDEOSOURCESGIXPROC ;
typedef  scalar_t__ PFNGLXCREATEGLXVIDEOSOURCESGIXPROC ;
typedef  scalar_t__ (* GLADloadproc ) (char*) ;

/* Variables and functions */
 int /*<<< orphan*/  GLAD_GLX_SGIX_video_source ; 
 scalar_t__ glad_glXCreateGLXVideoSourceSGIX ; 
 scalar_t__ glad_glXDestroyGLXVideoSourceSGIX ; 

__attribute__((used)) static void load_GLX_SGIX_video_source(GLADloadproc load) {
	if(!GLAD_GLX_SGIX_video_source) return;
#ifdef _VL_H_
	glad_glXCreateGLXVideoSourceSGIX = (PFNGLXCREATEGLXVIDEOSOURCESGIXPROC)load("glXCreateGLXVideoSourceSGIX");
	glad_glXDestroyGLXVideoSourceSGIX = (PFNGLXDESTROYGLXVIDEOSOURCESGIXPROC)load("glXDestroyGLXVideoSourceSGIX");
#else
	(void)load;
#endif
}