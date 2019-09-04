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
struct fbo_info {int /*<<< orphan*/  fbo; } ;

/* Variables and functions */
 int /*<<< orphan*/  bfree (struct fbo_info*) ; 
 int /*<<< orphan*/  glDeleteFramebuffers (int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  gl_success (char*) ; 

__attribute__((used)) static inline void fbo_info_destroy(struct fbo_info *fbo)
{
	if (fbo) {
		glDeleteFramebuffers(1, &fbo->fbo);
		gl_success("glDeleteFramebuffers");

		bfree(fbo);
	}
}