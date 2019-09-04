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
typedef  int __u32 ;

/* Variables and functions */
 int /*<<< orphan*/  mix (int,int,int) ; 

unsigned int ceph_str_hash_rjenkins(const char *str, unsigned int length)
{
	const unsigned char *k = (const unsigned char *)str;
	__u32 a, b, c;  /* the internal state */
	__u32 len;      /* how many key bytes still need mixing */

	/* Set up the internal state */
	len = length;
	a = 0x9e3779b9;      /* the golden ratio; an arbitrary value */
	b = a;
	c = 0;               /* variable initialization of internal state */

	/* handle most of the key */
	while (len >= 12) {
		a = a + (k[0] + ((__u32)k[1] << 8) + ((__u32)k[2] << 16) +
			 ((__u32)k[3] << 24));
		b = b + (k[4] + ((__u32)k[5] << 8) + ((__u32)k[6] << 16) +
			 ((__u32)k[7] << 24));
		c = c + (k[8] + ((__u32)k[9] << 8) + ((__u32)k[10] << 16) +
			 ((__u32)k[11] << 24));
		mix(a, b, c);
		k = k + 12;
		len = len - 12;
	}

	/* handle the last 11 bytes */
	c = c + length;
	switch (len) {
	case 11:
		c = c + ((__u32)k[10] << 24);
		/* fall through */
	case 10:
		c = c + ((__u32)k[9] << 16);
		/* fall through */
	case 9:
		c = c + ((__u32)k[8] << 8);
		/* the first byte of c is reserved for the length */
		/* fall through */
	case 8:
		b = b + ((__u32)k[7] << 24);
		/* fall through */
	case 7:
		b = b + ((__u32)k[6] << 16);
		/* fall through */
	case 6:
		b = b + ((__u32)k[5] << 8);
		/* fall through */
	case 5:
		b = b + k[4];
		/* fall through */
	case 4:
		a = a + ((__u32)k[3] << 24);
		/* fall through */
	case 3:
		a = a + ((__u32)k[2] << 16);
		/* fall through */
	case 2:
		a = a + ((__u32)k[1] << 8);
		/* fall through */
	case 1:
		a = a + k[0];
		/* case 0: nothing left to add */
	}
	mix(a, b, c);

	return c;
}