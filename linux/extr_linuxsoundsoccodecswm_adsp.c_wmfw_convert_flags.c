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
 unsigned int ADSP_MAX_STD_CTRL_SIZE ; 
 unsigned int SNDRV_CTL_ELEM_ACCESS_READ ; 
 unsigned int SNDRV_CTL_ELEM_ACCESS_TLV_CALLBACK ; 
 unsigned int SNDRV_CTL_ELEM_ACCESS_TLV_READ ; 
 unsigned int SNDRV_CTL_ELEM_ACCESS_TLV_WRITE ; 
 unsigned int SNDRV_CTL_ELEM_ACCESS_VOLATILE ; 
 unsigned int SNDRV_CTL_ELEM_ACCESS_WRITE ; 
 unsigned int WMFW_CTL_FLAG_READABLE ; 
 unsigned int WMFW_CTL_FLAG_VOLATILE ; 
 unsigned int WMFW_CTL_FLAG_WRITEABLE ; 

__attribute__((used)) static unsigned int wmfw_convert_flags(unsigned int in, unsigned int len)
{
	unsigned int out, rd, wr, vol;

	if (len > ADSP_MAX_STD_CTRL_SIZE) {
		rd = SNDRV_CTL_ELEM_ACCESS_TLV_READ;
		wr = SNDRV_CTL_ELEM_ACCESS_TLV_WRITE;
		vol = SNDRV_CTL_ELEM_ACCESS_VOLATILE;

		out = SNDRV_CTL_ELEM_ACCESS_TLV_CALLBACK;
	} else {
		rd = SNDRV_CTL_ELEM_ACCESS_READ;
		wr = SNDRV_CTL_ELEM_ACCESS_WRITE;
		vol = SNDRV_CTL_ELEM_ACCESS_VOLATILE;

		out = 0;
	}

	if (in) {
		if (in & WMFW_CTL_FLAG_READABLE)
			out |= rd;
		if (in & WMFW_CTL_FLAG_WRITEABLE)
			out |= wr;
		if (in & WMFW_CTL_FLAG_VOLATILE)
			out |= vol;
	} else {
		out |= rd | wr | vol;
	}

	return out;
}