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
struct fpgaimage {int dummy; } ;

/* Variables and functions */
 int EINVAL ; 
#define  f_bit 128 
 int get_imageformat () ; 
 int /*<<< orphan*/  gs_print_header (struct fpgaimage*) ; 
 int gs_read_bitstream (struct fpgaimage*) ; 
 int /*<<< orphan*/  pr_err (char*) ; 
 int /*<<< orphan*/  pr_info (char*) ; 

__attribute__((used)) static int gs_read_image(struct fpgaimage *fimage)
{
	int img_fmt;
	int err;

	img_fmt = get_imageformat();

	switch (img_fmt) {
	case f_bit:
		pr_info("image is bitstream format\n");
		err = gs_read_bitstream(fimage);
		if (err)
			return err;
		break;
	default:
		pr_err("unsupported fpga image format\n");
		return -EINVAL;
	}

	gs_print_header(fimage);

	return 0;
}