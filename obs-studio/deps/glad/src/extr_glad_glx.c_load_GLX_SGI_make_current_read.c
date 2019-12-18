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
typedef  scalar_t__ PFNGLXMAKECURRENTREADSGIPROC ;
typedef  scalar_t__ PFNGLXGETCURRENTREADDRAWABLESGIPROC ;
typedef  scalar_t__ (* GLADloadproc ) (char*) ;

/* Variables and functions */
 int /*<<< orphan*/  GLAD_GLX_SGI_make_current_read ; 
 scalar_t__ glad_glXGetCurrentReadDrawableSGI ; 
 scalar_t__ glad_glXMakeCurrentReadSGI ; 

__attribute__((used)) static void load_GLX_SGI_make_current_read(GLADloadproc load) {
	if(!GLAD_GLX_SGI_make_current_read) return;
	glad_glXMakeCurrentReadSGI = (PFNGLXMAKECURRENTREADSGIPROC)load("glXMakeCurrentReadSGI");
	glad_glXGetCurrentReadDrawableSGI = (PFNGLXGETCURRENTREADDRAWABLESGIPROC)load("glXGetCurrentReadDrawableSGI");
}