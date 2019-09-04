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
struct video_output_info {scalar_t__ format; int /*<<< orphan*/  height; } ;
struct video_frame {int /*<<< orphan*/  linesize; int /*<<< orphan*/  data; } ;
struct video_data {int /*<<< orphan*/ * linesize; int /*<<< orphan*/ * data; } ;

/* Variables and functions */
 int /*<<< orphan*/  LOG_ERROR ; 
 scalar_t__ VIDEO_FORMAT_I420 ; 
 scalar_t__ VIDEO_FORMAT_I444 ; 
 scalar_t__ VIDEO_FORMAT_NV12 ; 
 int /*<<< orphan*/  blog (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  compress_uyvx_to_i420 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  compress_uyvx_to_nv12 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  convert_uyvx_to_i444 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void convert_frame(
		struct video_frame *output, const struct video_data *input,
		const struct video_output_info *info)
{
	if (info->format == VIDEO_FORMAT_I420) {
		compress_uyvx_to_i420(
				input->data[0], input->linesize[0],
				0, info->height,
				output->data, output->linesize);

	} else if (info->format == VIDEO_FORMAT_NV12) {
		compress_uyvx_to_nv12(
				input->data[0], input->linesize[0],
				0, info->height,
				output->data, output->linesize);

	} else if (info->format == VIDEO_FORMAT_I444) {
		convert_uyvx_to_i444(
				input->data[0], input->linesize[0],
				0, info->height,
				output->data, output->linesize);

	} else {
		blog(LOG_ERROR, "convert_frame: unsupported texture format");
	}
}