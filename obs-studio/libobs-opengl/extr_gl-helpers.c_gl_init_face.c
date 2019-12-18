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
typedef  int /*<<< orphan*/  uint8_t ;
typedef  scalar_t__ uint32_t ;
typedef  int /*<<< orphan*/  GLint ;
typedef  int /*<<< orphan*/  GLenum ;

/* Variables and functions */
 int /*<<< orphan*/  glCompressedTexImage2D (int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ,scalar_t__,scalar_t__,int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  glTexImage2D (int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ,scalar_t__,scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  gl_success (char*) ; 

bool gl_init_face(GLenum target, GLenum type, uint32_t num_levels,
		  GLenum format, GLint internal_format, bool compressed,
		  uint32_t width, uint32_t height, uint32_t size,
		  const uint8_t ***p_data)
{
	bool success = true;
	const uint8_t **data = p_data ? *p_data : NULL;
	uint32_t i;

	for (i = 0; i < num_levels; i++) {
		if (compressed) {
			glCompressedTexImage2D(target, i, internal_format,
					       width, height, 0, size,
					       data ? *data : NULL);
			if (!gl_success("glCompressedTexImage2D"))
				success = false;

		} else {
			glTexImage2D(target, i, internal_format, width, height,
				     0, format, type, data ? *data : NULL);
			if (!gl_success("glTexImage2D"))
				success = false;
		}

		if (data)
			data++;

		size /= 4;
		width /= 2;
		height /= 2;

		if (width == 0)
			width = 1;
		if (height == 0)
			height = 1;
	}

	if (data)
		*p_data = data;
	return success;
}