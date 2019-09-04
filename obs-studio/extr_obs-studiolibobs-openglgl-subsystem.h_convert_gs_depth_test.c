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
typedef  enum gs_depth_test { ____Placeholder_gs_depth_test } gs_depth_test ;
typedef  int /*<<< orphan*/  GLenum ;

/* Variables and functions */
 int /*<<< orphan*/  GL_ALWAYS ; 
 int /*<<< orphan*/  GL_EQUAL ; 
 int /*<<< orphan*/  GL_GEQUAL ; 
 int /*<<< orphan*/  GL_GREATER ; 
 int /*<<< orphan*/  GL_LEQUAL ; 
 int /*<<< orphan*/  GL_LESS ; 
 int /*<<< orphan*/  GL_NEVER ; 
 int /*<<< orphan*/  GL_NOTEQUAL ; 
#define  GS_ALWAYS 135 
#define  GS_EQUAL 134 
#define  GS_GEQUAL 133 
#define  GS_GREATER 132 
#define  GS_LEQUAL 131 
#define  GS_LESS 130 
#define  GS_NEVER 129 
#define  GS_NOTEQUAL 128 

__attribute__((used)) static inline GLenum convert_gs_depth_test(enum gs_depth_test test)
{
	switch (test) {
	case GS_NEVER:    return GL_NEVER;
	case GS_LESS:     return GL_LESS;
	case GS_LEQUAL:   return GL_LEQUAL;
	case GS_EQUAL:    return GL_EQUAL;
	case GS_GEQUAL:   return GL_GEQUAL;
	case GS_GREATER:  return GL_GREATER;
	case GS_NOTEQUAL: return GL_NOTEQUAL;
	case GS_ALWAYS:   return GL_ALWAYS;
	}

	return GL_NEVER;
}