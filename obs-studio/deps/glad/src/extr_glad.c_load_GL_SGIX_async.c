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
typedef  scalar_t__ PFNGLPOLLASYNCSGIXPROC ;
typedef  scalar_t__ PFNGLISASYNCMARKERSGIXPROC ;
typedef  scalar_t__ PFNGLGENASYNCMARKERSSGIXPROC ;
typedef  scalar_t__ PFNGLFINISHASYNCSGIXPROC ;
typedef  scalar_t__ PFNGLDELETEASYNCMARKERSSGIXPROC ;
typedef  scalar_t__ PFNGLASYNCMARKERSGIXPROC ;
typedef  scalar_t__ (* GLADloadproc ) (char*) ;

/* Variables and functions */
 int /*<<< orphan*/  GLAD_GL_SGIX_async ; 
 scalar_t__ glad_glAsyncMarkerSGIX ; 
 scalar_t__ glad_glDeleteAsyncMarkersSGIX ; 
 scalar_t__ glad_glFinishAsyncSGIX ; 
 scalar_t__ glad_glGenAsyncMarkersSGIX ; 
 scalar_t__ glad_glIsAsyncMarkerSGIX ; 
 scalar_t__ glad_glPollAsyncSGIX ; 

__attribute__((used)) static void load_GL_SGIX_async(GLADloadproc load) {
	if(!GLAD_GL_SGIX_async) return;
	glad_glAsyncMarkerSGIX = (PFNGLASYNCMARKERSGIXPROC)load("glAsyncMarkerSGIX");
	glad_glFinishAsyncSGIX = (PFNGLFINISHASYNCSGIXPROC)load("glFinishAsyncSGIX");
	glad_glPollAsyncSGIX = (PFNGLPOLLASYNCSGIXPROC)load("glPollAsyncSGIX");
	glad_glGenAsyncMarkersSGIX = (PFNGLGENASYNCMARKERSSGIXPROC)load("glGenAsyncMarkersSGIX");
	glad_glDeleteAsyncMarkersSGIX = (PFNGLDELETEASYNCMARKERSSGIXPROC)load("glDeleteAsyncMarkersSGIX");
	glad_glIsAsyncMarkerSGIX = (PFNGLISASYNCMARKERSGIXPROC)load("glIsAsyncMarkerSGIX");
}