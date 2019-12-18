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
typedef  int uint32_t ;
struct iio_channel_info {int shift; int mask; int bits_used; float offset; float scale; scalar_t__ is_signed; scalar_t__ be; } ;
typedef  int int32_t ;

/* Variables and functions */
 int be32toh (int) ; 
 int le32toh (int) ; 
 int /*<<< orphan*/  printf (char*,float) ; 

void print4byte(uint32_t input, struct iio_channel_info *info)
{
	/* First swap if incorrect endian */
	if (info->be)
		input = be32toh(input);
	else
		input = le32toh(input);

	/*
	 * Shift before conversion to avoid sign extension
	 * of left aligned data
	 */
	input >>= info->shift;
	input &= info->mask;
	if (info->is_signed) {
		int32_t val = (int32_t)(input << (32 - info->bits_used)) >>
			      (32 - info->bits_used);
		printf("%05f ", ((float)val + info->offset) * info->scale);
	} else {
		printf("%05f ", ((float)input + info->offset) * info->scale);
	}
}