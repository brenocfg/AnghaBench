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
typedef  scalar_t__ PFNGLTEXSUBIMAGE2DEXTPROC ;
typedef  scalar_t__ PFNGLTEXSUBIMAGE1DEXTPROC ;
typedef  scalar_t__ (* GLADloadproc ) (char*) ;

/* Variables and functions */
 int /*<<< orphan*/  GLAD_GL_EXT_subtexture ; 
 scalar_t__ glad_glTexSubImage1DEXT ; 
 scalar_t__ glad_glTexSubImage2DEXT ; 

__attribute__((used)) static void load_GL_EXT_subtexture(GLADloadproc load) {
	if(!GLAD_GL_EXT_subtexture) return;
	glad_glTexSubImage1DEXT = (PFNGLTEXSUBIMAGE1DEXTPROC)load("glTexSubImage1DEXT");
	glad_glTexSubImage2DEXT = (PFNGLTEXSUBIMAGE2DEXTPROC)load("glTexSubImage2DEXT");
}