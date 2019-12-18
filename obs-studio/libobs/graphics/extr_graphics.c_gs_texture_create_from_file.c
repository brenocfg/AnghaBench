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
typedef  int /*<<< orphan*/  uint32_t ;
typedef  int /*<<< orphan*/  gs_texture_t ;
typedef  enum gs_color_format { ____Placeholder_gs_color_format } gs_color_format ;

/* Variables and functions */
 int /*<<< orphan*/  bfree (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * gs_create_texture_file_data (char const*,int*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * gs_texture_create (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int,int /*<<< orphan*/  const**,int /*<<< orphan*/ ) ; 

gs_texture_t *gs_texture_create_from_file(const char *file)
{
	enum gs_color_format format;
	uint32_t cx;
	uint32_t cy;
	uint8_t *data = gs_create_texture_file_data(file, &format, &cx, &cy);
	gs_texture_t *tex = NULL;

	if (data) {
		tex = gs_texture_create(cx, cy, format, 1,
					(const uint8_t **)&data, 0);
		bfree(data);
	}

	return tex;
}