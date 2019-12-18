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
typedef  scalar_t__ PFNGLXCOPYIMAGESUBDATANVPROC ;
typedef  scalar_t__ (* GLADloadproc ) (char*) ;

/* Variables and functions */
 int /*<<< orphan*/  GLAD_GLX_NV_copy_image ; 
 scalar_t__ glad_glXCopyImageSubDataNV ; 

__attribute__((used)) static void load_GLX_NV_copy_image(GLADloadproc load) {
	if(!GLAD_GLX_NV_copy_image) return;
	glad_glXCopyImageSubDataNV = (PFNGLXCOPYIMAGESUBDATANVPROC)load("glXCopyImageSubDataNV");
}