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
struct TYPE_2__ {int* texture_ready; int* texture_mapped; int /*<<< orphan*/ * pbos; } ;
typedef  int /*<<< orphan*/  GLvoid ;

/* Variables and functions */
 int /*<<< orphan*/  GL_PIXEL_PACK_BUFFER ; 
 int /*<<< orphan*/  GL_READ_ONLY ; 
 int NUM_BUFFERS ; 
 TYPE_1__ data ; 
 int /*<<< orphan*/  glBindBuffer (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * glMapBuffer (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ gl_error (char*,char*) ; 
 int /*<<< orphan*/  shmem_copy_data (int,int /*<<< orphan*/ *) ; 

__attribute__((used)) static inline void gl_shmem_capture_queue_copy(void)
{
	for (int i = 0; i < NUM_BUFFERS; i++) {
		if (data.texture_ready[i]) {
			GLvoid *buffer;

			data.texture_ready[i] = false;

			glBindBuffer(GL_PIXEL_PACK_BUFFER, data.pbos[i]);
			if (gl_error("gl_shmem_capture_queue_copy",
				     "failed to bind pbo")) {
				return;
			}

			buffer =
				glMapBuffer(GL_PIXEL_PACK_BUFFER, GL_READ_ONLY);
			if (buffer) {
				data.texture_mapped[i] = true;
				shmem_copy_data(i, buffer);
			}
			break;
		}
	}
}