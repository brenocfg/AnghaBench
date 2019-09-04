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
typedef  scalar_t__ PFNGLELEMENTPOINTERATIPROC ;
typedef  scalar_t__ PFNGLDRAWRANGEELEMENTARRAYATIPROC ;
typedef  scalar_t__ PFNGLDRAWELEMENTARRAYATIPROC ;
typedef  scalar_t__ (* GLADloadproc ) (char*) ;

/* Variables and functions */
 int /*<<< orphan*/  GLAD_GL_ATI_element_array ; 
 scalar_t__ glad_glDrawElementArrayATI ; 
 scalar_t__ glad_glDrawRangeElementArrayATI ; 
 scalar_t__ glad_glElementPointerATI ; 

__attribute__((used)) static void load_GL_ATI_element_array(GLADloadproc load) {
	if(!GLAD_GL_ATI_element_array) return;
	glad_glElementPointerATI = (PFNGLELEMENTPOINTERATIPROC)load("glElementPointerATI");
	glad_glDrawElementArrayATI = (PFNGLDRAWELEMENTARRAYATIPROC)load("glDrawElementArrayATI");
	glad_glDrawRangeElementArrayATI = (PFNGLDRAWRANGEELEMENTARRAYATIPROC)load("glDrawRangeElementArrayATI");
}