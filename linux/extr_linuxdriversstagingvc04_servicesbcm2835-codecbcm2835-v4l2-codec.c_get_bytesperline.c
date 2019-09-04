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
struct bcm2835_codec_fmt {int depth; int /*<<< orphan*/  bytesperline_align; } ;

/* Variables and functions */
 unsigned int ALIGN (int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline unsigned int get_bytesperline(int width,
					    struct bcm2835_codec_fmt *fmt)
{
	return ALIGN((width * fmt->depth) >> 3, fmt->bytesperline_align);
}