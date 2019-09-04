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
typedef  scalar_t__ GLenum ;

/* Variables and functions */
 scalar_t__ GL_NO_ERROR ; 
 int /*<<< orphan*/  LOG_ERROR ; 
 int /*<<< orphan*/  blog (int /*<<< orphan*/ ,char*,char const*,scalar_t__) ; 
 scalar_t__ glGetError () ; 

__attribute__((used)) static inline bool gl_success(const char *funcname)
{
	GLenum errorcode = glGetError();
	if (errorcode != GL_NO_ERROR) {
		blog(LOG_ERROR, "%s failed, glGetError returned 0x%X",
				funcname, errorcode);
		return false;
	}

	return true;
}