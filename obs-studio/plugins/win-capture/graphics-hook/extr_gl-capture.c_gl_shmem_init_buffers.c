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
typedef  int uint32_t ;
struct TYPE_2__ {int cx; int cy; int /*<<< orphan*/  textures; int /*<<< orphan*/  pbos; } ;
typedef  int /*<<< orphan*/  GLint ;

/* Variables and functions */
 int /*<<< orphan*/  GL_PIXEL_PACK_BUFFER ; 
 int /*<<< orphan*/  GL_PIXEL_PACK_BUFFER_BINDING ; 
 int /*<<< orphan*/  GL_TEXTURE_2D ; 
 int /*<<< orphan*/  GL_TEXTURE_BINDING_2D ; 
 size_t NUM_BUFFERS ; 
 TYPE_1__ data ; 
 int /*<<< orphan*/  glBindBuffer (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  glBindTexture (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  glGenBuffers (size_t,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  glGenTextures (size_t,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  glGetIntegerv (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ gl_error (char*,char*) ; 
 int /*<<< orphan*/  gl_shmem_init_data (size_t,int) ; 

__attribute__((used)) static inline bool gl_shmem_init_buffers(void)
{
	uint32_t size = data.cx * data.cy * 4;
	GLint last_pbo;
	GLint last_tex;

	glGenBuffers(NUM_BUFFERS, data.pbos);
	if (gl_error("gl_shmem_init_buffers", "failed to generate buffers")) {
		return false;
	}

	glGenTextures(NUM_BUFFERS, data.textures);
	if (gl_error("gl_shmem_init_buffers", "failed to generate textures")) {
		return false;
	}

	glGetIntegerv(GL_PIXEL_PACK_BUFFER_BINDING, &last_pbo);
	if (gl_error("gl_shmem_init_buffers",
		     "failed to save pixel pack buffer")) {
		return false;
	}

	glGetIntegerv(GL_TEXTURE_BINDING_2D, &last_tex);
	if (gl_error("gl_shmem_init_buffers", "failed to save texture")) {
		return false;
	}

	for (size_t i = 0; i < NUM_BUFFERS; i++) {
		if (!gl_shmem_init_data(i, size)) {
			return false;
		}
	}

	glBindBuffer(GL_PIXEL_PACK_BUFFER, last_pbo);
	glBindTexture(GL_TEXTURE_2D, last_tex);
	return true;
}