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
typedef  scalar_t__ PFNGLTEXSUBIMAGE3DEXTPROC ;
typedef  scalar_t__ PFNGLTEXIMAGE3DEXTPROC ;
typedef  scalar_t__ (* GLADloadproc ) (char*) ;

/* Variables and functions */
 int /*<<< orphan*/  GLAD_GL_EXT_texture3D ; 
 scalar_t__ glad_glTexImage3DEXT ; 
 scalar_t__ glad_glTexSubImage3DEXT ; 

__attribute__((used)) static void load_GL_EXT_texture3D(GLADloadproc load) {
	if(!GLAD_GL_EXT_texture3D) return;
	glad_glTexImage3DEXT = (PFNGLTEXIMAGE3DEXTPROC)load("glTexImage3DEXT");
	glad_glTexSubImage3DEXT = (PFNGLTEXSUBIMAGE3DEXTPROC)load("glTexSubImage3DEXT");
}