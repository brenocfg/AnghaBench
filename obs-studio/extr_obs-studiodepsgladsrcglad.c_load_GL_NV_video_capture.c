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
typedef  scalar_t__ PFNGLVIDEOCAPTURESTREAMPARAMETERIVNVPROC ;
typedef  scalar_t__ PFNGLVIDEOCAPTURESTREAMPARAMETERFVNVPROC ;
typedef  scalar_t__ PFNGLVIDEOCAPTURESTREAMPARAMETERDVNVPROC ;
typedef  scalar_t__ PFNGLVIDEOCAPTURENVPROC ;
typedef  scalar_t__ PFNGLGETVIDEOCAPTURESTREAMIVNVPROC ;
typedef  scalar_t__ PFNGLGETVIDEOCAPTURESTREAMFVNVPROC ;
typedef  scalar_t__ PFNGLGETVIDEOCAPTURESTREAMDVNVPROC ;
typedef  scalar_t__ PFNGLGETVIDEOCAPTUREIVNVPROC ;
typedef  scalar_t__ PFNGLENDVIDEOCAPTURENVPROC ;
typedef  scalar_t__ PFNGLBINDVIDEOCAPTURESTREAMTEXTURENVPROC ;
typedef  scalar_t__ PFNGLBINDVIDEOCAPTURESTREAMBUFFERNVPROC ;
typedef  scalar_t__ PFNGLBEGINVIDEOCAPTURENVPROC ;
typedef  scalar_t__ (* GLADloadproc ) (char*) ;

/* Variables and functions */
 int /*<<< orphan*/  GLAD_GL_NV_video_capture ; 
 scalar_t__ glad_glBeginVideoCaptureNV ; 
 scalar_t__ glad_glBindVideoCaptureStreamBufferNV ; 
 scalar_t__ glad_glBindVideoCaptureStreamTextureNV ; 
 scalar_t__ glad_glEndVideoCaptureNV ; 
 scalar_t__ glad_glGetVideoCaptureStreamdvNV ; 
 scalar_t__ glad_glGetVideoCaptureStreamfvNV ; 
 scalar_t__ glad_glGetVideoCaptureStreamivNV ; 
 scalar_t__ glad_glGetVideoCaptureivNV ; 
 scalar_t__ glad_glVideoCaptureNV ; 
 scalar_t__ glad_glVideoCaptureStreamParameterdvNV ; 
 scalar_t__ glad_glVideoCaptureStreamParameterfvNV ; 
 scalar_t__ glad_glVideoCaptureStreamParameterivNV ; 

__attribute__((used)) static void load_GL_NV_video_capture(GLADloadproc load) {
	if(!GLAD_GL_NV_video_capture) return;
	glad_glBeginVideoCaptureNV = (PFNGLBEGINVIDEOCAPTURENVPROC)load("glBeginVideoCaptureNV");
	glad_glBindVideoCaptureStreamBufferNV = (PFNGLBINDVIDEOCAPTURESTREAMBUFFERNVPROC)load("glBindVideoCaptureStreamBufferNV");
	glad_glBindVideoCaptureStreamTextureNV = (PFNGLBINDVIDEOCAPTURESTREAMTEXTURENVPROC)load("glBindVideoCaptureStreamTextureNV");
	glad_glEndVideoCaptureNV = (PFNGLENDVIDEOCAPTURENVPROC)load("glEndVideoCaptureNV");
	glad_glGetVideoCaptureivNV = (PFNGLGETVIDEOCAPTUREIVNVPROC)load("glGetVideoCaptureivNV");
	glad_glGetVideoCaptureStreamivNV = (PFNGLGETVIDEOCAPTURESTREAMIVNVPROC)load("glGetVideoCaptureStreamivNV");
	glad_glGetVideoCaptureStreamfvNV = (PFNGLGETVIDEOCAPTURESTREAMFVNVPROC)load("glGetVideoCaptureStreamfvNV");
	glad_glGetVideoCaptureStreamdvNV = (PFNGLGETVIDEOCAPTURESTREAMDVNVPROC)load("glGetVideoCaptureStreamdvNV");
	glad_glVideoCaptureNV = (PFNGLVIDEOCAPTURENVPROC)load("glVideoCaptureNV");
	glad_glVideoCaptureStreamParameterivNV = (PFNGLVIDEOCAPTURESTREAMPARAMETERIVNVPROC)load("glVideoCaptureStreamParameterivNV");
	glad_glVideoCaptureStreamParameterfvNV = (PFNGLVIDEOCAPTURESTREAMPARAMETERFVNVPROC)load("glVideoCaptureStreamParameterfvNV");
	glad_glVideoCaptureStreamParameterdvNV = (PFNGLVIDEOCAPTURESTREAMPARAMETERDVNVPROC)load("glVideoCaptureStreamParameterdvNV");
}