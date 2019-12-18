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
struct vec4 {int dummy; } ;
struct obs_video_info {int /*<<< orphan*/  range; int /*<<< orphan*/  colorspace; int /*<<< orphan*/  output_format; } ;
struct obs_core_video {int /*<<< orphan*/  color_matrix; } ;
struct matrix4 {struct vec4 y; struct vec4 x; } ;

/* Variables and functions */
 scalar_t__ format_is_yuv (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  matrix4_identity (struct matrix4*) ; 
 int /*<<< orphan*/  matrix4_inv (struct matrix4*,struct matrix4*) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,struct matrix4*,int) ; 
 int /*<<< orphan*/  video_format_get_parameters (int /*<<< orphan*/ ,int /*<<< orphan*/ ,float*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static inline void set_video_matrix(struct obs_core_video *video,
				    struct obs_video_info *ovi)
{
	struct matrix4 mat;
	struct vec4 r_row;

	if (format_is_yuv(ovi->output_format)) {
		video_format_get_parameters(ovi->colorspace, ovi->range,
					    (float *)&mat, NULL, NULL);
		matrix4_inv(&mat, &mat);

		/* swap R and G */
		r_row = mat.x;
		mat.x = mat.y;
		mat.y = r_row;
	} else {
		matrix4_identity(&mat);
	}

	memcpy(video->color_matrix, &mat, sizeof(float) * 16);
}