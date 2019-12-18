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
 int EBADMSG ; 
 int ENOBUFS ; 
 int snprintf (char*,size_t,char*,...) ; 

int sprint_oid(const void *data, size_t datasize, char *buffer, size_t bufsize)
{
	const unsigned char *v = data, *end = v + datasize;
	unsigned long num;
	unsigned char n;
	size_t ret;
	int count;

	if (v >= end)
		goto bad;

	n = *v++;
	ret = count = snprintf(buffer, bufsize, "%u.%u", n / 40, n % 40);
	if (count >= bufsize)
		return -ENOBUFS;
	buffer += count;
	bufsize -= count;

	while (v < end) {
		num = 0;
		n = *v++;
		if (!(n & 0x80)) {
			num = n;
		} else {
			num = n & 0x7f;
			do {
				if (v >= end)
					goto bad;
				n = *v++;
				num <<= 7;
				num |= n & 0x7f;
			} while (n & 0x80);
		}
		ret += count = snprintf(buffer, bufsize, ".%lu", num);
		if (count >= bufsize)
			return -ENOBUFS;
		buffer += count;
		bufsize -= count;
	}

	return ret;

bad:
	snprintf(buffer, bufsize, "(bad)");
	return -EBADMSG;
}