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
typedef  scalar_t__ PFNGLXCOPYSUBBUFFERMESAPROC ;
typedef  scalar_t__ (* GLADloadproc ) (char*) ;

/* Variables and functions */
 int /*<<< orphan*/  GLAD_GLX_MESA_copy_sub_buffer ; 
 scalar_t__ glad_glXCopySubBufferMESA ; 

__attribute__((used)) static void load_GLX_MESA_copy_sub_buffer(GLADloadproc load) {
	if(!GLAD_GLX_MESA_copy_sub_buffer) return;
	glad_glXCopySubBufferMESA = (PFNGLXCOPYSUBBUFFERMESAPROC)load("glXCopySubBufferMESA");
}