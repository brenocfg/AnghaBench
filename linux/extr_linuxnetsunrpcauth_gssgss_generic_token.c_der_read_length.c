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
 unsigned char SIZEOF_INT ; 

__attribute__((used)) static int
der_read_length(unsigned char **buf, int *bufsize)
{
	unsigned char sf;
	int ret;

	if (*bufsize < 1)
		return -1;
	sf = *(*buf)++;
	(*bufsize)--;
	if (sf & 0x80) {
		if ((sf &= 0x7f) > ((*bufsize)-1))
			return -1;
		if (sf > SIZEOF_INT)
			return -1;
		ret = 0;
		for (; sf; sf--) {
			ret = (ret<<8) + (*(*buf)++);
			(*bufsize)--;
		}
	} else {
		ret = sf;
	}

	return ret;
}