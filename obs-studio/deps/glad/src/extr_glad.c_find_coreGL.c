#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {int major; int minor; } ;

/* Variables and functions */
 int GLAD_GL_VERSION_1_0 ; 
 int GLAD_GL_VERSION_1_1 ; 
 int GLAD_GL_VERSION_1_2 ; 
 int GLAD_GL_VERSION_1_3 ; 
 int GLAD_GL_VERSION_1_4 ; 
 int GLAD_GL_VERSION_1_5 ; 
 int GLAD_GL_VERSION_2_0 ; 
 int GLAD_GL_VERSION_2_1 ; 
 int GLAD_GL_VERSION_3_0 ; 
 int GLAD_GL_VERSION_3_1 ; 
 int GLAD_GL_VERSION_3_2 ; 
 int GLAD_GL_VERSION_3_3 ; 
 int GLAD_GL_VERSION_4_0 ; 
 int GLAD_GL_VERSION_4_1 ; 
 int GLAD_GL_VERSION_4_2 ; 
 int GLAD_GL_VERSION_4_3 ; 
 int GLAD_GL_VERSION_4_4 ; 
 TYPE_1__ GLVersion ; 
 int /*<<< orphan*/  GL_VERSION ; 
 scalar_t__ glGetString (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void find_coreGL(void) {
	const char *v = (const char *)glGetString(GL_VERSION);
	int major = v[0] - '0';
	int minor = v[2] - '0';
	GLVersion.major = major; GLVersion.minor = minor;
	GLAD_GL_VERSION_1_0 = (major == 1 && minor >= 0) || major > 1;
	GLAD_GL_VERSION_1_1 = (major == 1 && minor >= 1) || major > 1;
	GLAD_GL_VERSION_1_2 = (major == 1 && minor >= 2) || major > 1;
	GLAD_GL_VERSION_1_3 = (major == 1 && minor >= 3) || major > 1;
	GLAD_GL_VERSION_1_4 = (major == 1 && minor >= 4) || major > 1;
	GLAD_GL_VERSION_1_5 = (major == 1 && minor >= 5) || major > 1;
	GLAD_GL_VERSION_2_0 = (major == 2 && minor >= 0) || major > 2;
	GLAD_GL_VERSION_2_1 = (major == 2 && minor >= 1) || major > 2;
	GLAD_GL_VERSION_3_0 = (major == 3 && minor >= 0) || major > 3;
	GLAD_GL_VERSION_3_1 = (major == 3 && minor >= 1) || major > 3;
	GLAD_GL_VERSION_3_2 = (major == 3 && minor >= 2) || major > 3;
	GLAD_GL_VERSION_3_3 = (major == 3 && minor >= 3) || major > 3;
	GLAD_GL_VERSION_4_0 = (major == 4 && minor >= 0) || major > 4;
	GLAD_GL_VERSION_4_1 = (major == 4 && minor >= 1) || major > 4;
	GLAD_GL_VERSION_4_2 = (major == 4 && minor >= 2) || major > 4;
	GLAD_GL_VERSION_4_3 = (major == 4 && minor >= 3) || major > 4;
	GLAD_GL_VERSION_4_4 = (major == 4 && minor >= 4) || major > 4;
}