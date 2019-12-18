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
typedef  size_t uint32_t ;

/* Variables and functions */
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,int /*<<< orphan*/  const*,size_t) ; 

__attribute__((used)) static const uint8_t *set_gpu_converted_plane(uint32_t width, uint32_t height,
					      uint32_t linesize_input,
					      uint32_t linesize_output,
					      const uint8_t *in, uint8_t *out)
{
	if ((width == linesize_input) && (width == linesize_output)) {
		size_t total = width * height;
		memcpy(out, in, total);
		in += total;
	} else {
		for (size_t y = 0; y < height; y++) {
			memcpy(out, in, width);
			out += linesize_output;
			in += linesize_input;
		}
	}

	return in;
}