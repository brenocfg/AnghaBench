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
typedef  scalar_t__ PFNGLSTRINGMARKERGREMEDYPROC ;
typedef  scalar_t__ (* GLADloadproc ) (char*) ;

/* Variables and functions */
 int /*<<< orphan*/  GLAD_GL_GREMEDY_string_marker ; 
 scalar_t__ glad_glStringMarkerGREMEDY ; 

__attribute__((used)) static void load_GL_GREMEDY_string_marker(GLADloadproc load) {
	if(!GLAD_GL_GREMEDY_string_marker) return;
	glad_glStringMarkerGREMEDY = (PFNGLSTRINGMARKERGREMEDYPROC)load("glStringMarkerGREMEDY");
}