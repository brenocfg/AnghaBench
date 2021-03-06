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
typedef  int /*<<< orphan*/  GLenum ;

/* Variables and functions */
 int /*<<< orphan*/  glCullFace (int /*<<< orphan*/ ) ; 
 int gl_success (char*) ; 

__attribute__((used)) static inline bool gl_cull_face(GLenum faces)
{
	glCullFace(faces);
	return gl_success("glCullFace");
}