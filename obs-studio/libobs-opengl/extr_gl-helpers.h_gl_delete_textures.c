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
typedef  int /*<<< orphan*/  GLuint ;
typedef  int /*<<< orphan*/  GLsizei ;

/* Variables and functions */
 int /*<<< orphan*/  glDeleteTextures (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  gl_success (char*) ; 

__attribute__((used)) static inline void gl_delete_textures(GLsizei num_buffers, GLuint *buffers)
{
	glDeleteTextures(num_buffers, buffers);
	gl_success("glDeleteTextures");
}