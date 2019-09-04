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
typedef  enum AVPixelFormat { ____Placeholder_AVPixelFormat } AVPixelFormat ;

/* Variables and functions */
 int const AV_PIX_FMT_NONE ; 

__attribute__((used)) static enum AVPixelFormat get_best_format(
		const enum AVPixelFormat *best,
		const enum AVPixelFormat *formats)
{
	while (*best != AV_PIX_FMT_NONE) {
		enum AVPixelFormat best_format = *best;
		const enum AVPixelFormat *cur_formats = formats;

		while (*cur_formats != AV_PIX_FMT_NONE) {
			enum AVPixelFormat avail_format = *cur_formats;

			if (best_format == avail_format)
				return best_format;

			cur_formats++;
		}

		best++;
	}

	return AV_PIX_FMT_NONE;
}