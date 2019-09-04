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
typedef  scalar_t__ PFNGLTEXSTORAGE3DPROC ;
typedef  scalar_t__ PFNGLTEXSTORAGE2DPROC ;
typedef  scalar_t__ PFNGLTEXSTORAGE1DPROC ;
typedef  scalar_t__ (* GLADloadproc ) (char*) ;

/* Variables and functions */
 int /*<<< orphan*/  GLAD_GL_ARB_texture_storage ; 
 scalar_t__ glad_glTexStorage1D ; 
 scalar_t__ glad_glTexStorage2D ; 
 scalar_t__ glad_glTexStorage3D ; 

__attribute__((used)) static void load_GL_ARB_texture_storage(GLADloadproc load) {
	if(!GLAD_GL_ARB_texture_storage) return;
	glad_glTexStorage1D = (PFNGLTEXSTORAGE1DPROC)load("glTexStorage1D");
	glad_glTexStorage2D = (PFNGLTEXSTORAGE2DPROC)load("glTexStorage2D");
	glad_glTexStorage3D = (PFNGLTEXSTORAGE3DPROC)load("glTexStorage3D");
}