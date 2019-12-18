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
 scalar_t__ der_length_size (int) ; 

__attribute__((used)) static void
der_write_length(unsigned char **buf, int length)
{
	if (length < (1<<7)) {
		*(*buf)++ = (unsigned char) length;
	} else {
		*(*buf)++ = (unsigned char) (der_length_size(length)+127);
#if (SIZEOF_INT > 2)
		if (length >= (1<<24))
			*(*buf)++ = (unsigned char) (length>>24);
		if (length >= (1<<16))
			*(*buf)++ = (unsigned char) ((length>>16)&0xff);
#endif
		if (length >= (1<<8))
			*(*buf)++ = (unsigned char) ((length>>8)&0xff);
		*(*buf)++ = (unsigned char) (length&0xff);
	}
}