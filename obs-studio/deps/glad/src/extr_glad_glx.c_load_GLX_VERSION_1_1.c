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
typedef  scalar_t__ PFNGLXQUERYSERVERSTRINGPROC ;
typedef  scalar_t__ PFNGLXQUERYEXTENSIONSSTRINGPROC ;
typedef  scalar_t__ PFNGLXGETCLIENTSTRINGPROC ;
typedef  scalar_t__ (* GLADloadproc ) (char*) ;

/* Variables and functions */
 int /*<<< orphan*/  GLAD_GLX_VERSION_1_1 ; 
 scalar_t__ glad_glXGetClientString ; 
 scalar_t__ glad_glXQueryExtensionsString ; 
 scalar_t__ glad_glXQueryServerString ; 

__attribute__((used)) static void load_GLX_VERSION_1_1(GLADloadproc load) {
	if(!GLAD_GLX_VERSION_1_1) return;
	glad_glXQueryExtensionsString = (PFNGLXQUERYEXTENSIONSSTRINGPROC)load("glXQueryExtensionsString");
	glad_glXQueryServerString = (PFNGLXQUERYSERVERSTRINGPROC)load("glXQueryServerString");
	glad_glXGetClientString = (PFNGLXGETCLIENTSTRINGPROC)load("glXGetClientString");
}