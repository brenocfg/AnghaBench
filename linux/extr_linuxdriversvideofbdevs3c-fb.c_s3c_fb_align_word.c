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

/* Variables and functions */
 int ALIGN (unsigned int,int) ; 

__attribute__((used)) static int s3c_fb_align_word(unsigned int bpp, unsigned int pix)
{
	int pix_per_word;

	if (bpp > 16)
		return pix;

	pix_per_word = (8 * 32) / bpp;
	return ALIGN(pix, pix_per_word);
}