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
typedef  scalar_t__ PFNGLXGETPROCADDRESSPROC ;
typedef  scalar_t__ (* GLADloadproc ) (char*) ;

/* Variables and functions */
 int /*<<< orphan*/  GLAD_GLX_VERSION_1_4 ; 
 scalar_t__ glad_glXGetProcAddress ; 

__attribute__((used)) static void load_GLX_VERSION_1_4(GLADloadproc load) {
	if(!GLAD_GLX_VERSION_1_4) return;
	glad_glXGetProcAddress = (PFNGLXGETPROCADDRESSPROC)load("glXGetProcAddress");
}