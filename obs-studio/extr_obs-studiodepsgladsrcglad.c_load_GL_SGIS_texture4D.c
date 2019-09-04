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
typedef  scalar_t__ PFNGLTEXSUBIMAGE4DSGISPROC ;
typedef  scalar_t__ PFNGLTEXIMAGE4DSGISPROC ;
typedef  scalar_t__ (* GLADloadproc ) (char*) ;

/* Variables and functions */
 int /*<<< orphan*/  GLAD_GL_SGIS_texture4D ; 
 scalar_t__ glad_glTexImage4DSGIS ; 
 scalar_t__ glad_glTexSubImage4DSGIS ; 

__attribute__((used)) static void load_GL_SGIS_texture4D(GLADloadproc load) {
	if(!GLAD_GL_SGIS_texture4D) return;
	glad_glTexImage4DSGIS = (PFNGLTEXIMAGE4DSGISPROC)load("glTexImage4DSGIS");
	glad_glTexSubImage4DSGIS = (PFNGLTEXSUBIMAGE4DSGISPROC)load("glTexSubImage4DSGIS");
}