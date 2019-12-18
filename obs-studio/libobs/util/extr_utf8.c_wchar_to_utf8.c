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
typedef  int wchar_t ;

/* Variables and functions */
 int UTF8_IGNORE_ERROR ; 
 int UTF8_SKIP_BOM ; 
 int _BOM ; 
 unsigned char _NXT ; 
 unsigned char _SEQ2 ; 
 unsigned char _SEQ3 ; 
 unsigned char _SEQ4 ; 
 unsigned char _SEQ5 ; 
 unsigned char _SEQ6 ; 
 scalar_t__ wchar_forbidden (int) ; 

size_t wchar_to_utf8(const wchar_t *in, size_t insize, char *out,
		     size_t outsize, int flags)
{
	wchar_t *w, *wlim, ch = 0;
	unsigned char *p, *lim, *oc;
	size_t total, n;

	if (in == NULL || (outsize == 0 && out != NULL))
		return 0;

	w = (wchar_t *)in;
	wlim = (insize != 0) ? (w + insize) : (wchar_t *)-1;
	p = (unsigned char *)out;
	lim = p + outsize;
	total = 0;

	for (; w < wlim; w++) {
		if (!*w)
			break;

		if (wchar_forbidden(*w) != 0) {
			if ((flags & UTF8_IGNORE_ERROR) == 0)
				return 0;
			else
				continue;
		}

		if (*w == _BOM && (flags & UTF8_SKIP_BOM) != 0)
			continue;

		if (*w < 0) {
			if ((flags & UTF8_IGNORE_ERROR) == 0)
				return 0;
			continue;
		} else if (*w <= 0x0000007f)
			n = 1;
		else if (*w <= 0x000007ff)
			n = 2;
		else if (*w <= 0x0000ffff)
			n = 3;
		else if (*w <= 0x001fffff)
			n = 4;
		else if (*w <= 0x03ffffff)
			n = 5;
		else /* if (*w <= 0x7fffffff) */
			n = 6;

		total += n;

		if (out == NULL)
			continue;

		if ((size_t)(lim - p) <= n - 1)
			return 0; /* no space left */

		ch = *w;
		oc = (unsigned char *)&ch;
		switch (n) {
		case 1:
			*p = oc[0];
			break;

		case 2:
			p[1] = _NXT | (oc[0] & 0x3f);
			p[0] = _SEQ2 | (oc[0] >> 6) | ((oc[1] & 0x07) << 2);
			break;

		case 3:
			p[2] = _NXT | (oc[0] & 0x3f);
			p[1] = _NXT | (oc[0] >> 6) | ((oc[1] & 0x0f) << 2);
			p[0] = _SEQ3 | ((oc[1] & 0xf0) >> 4);
			break;

		case 4:
			p[3] = _NXT | (oc[0] & 0x3f);
			p[2] = _NXT | (oc[0] >> 6) | ((oc[1] & 0x0f) << 2);
			p[1] = _NXT | ((oc[1] & 0xf0) >> 4) |
			       ((oc[2] & 0x03) << 4);
			p[0] = _SEQ4 | ((oc[2] & 0x1f) >> 2);
			break;

		case 5:
			p[4] = _NXT | (oc[0] & 0x3f);
			p[3] = _NXT | (oc[0] >> 6) | ((oc[1] & 0x0f) << 2);
			p[2] = _NXT | ((oc[1] & 0xf0) >> 4) |
			       ((oc[2] & 0x03) << 4);
			p[1] = _NXT | (oc[2] >> 2);
			p[0] = _SEQ5 | (oc[3] & 0x03);
			break;

		case 6:
			p[5] = _NXT | (oc[0] & 0x3f);
			p[4] = _NXT | (oc[0] >> 6) | ((oc[1] & 0x0f) << 2);
			p[3] = _NXT | (oc[1] >> 4) | ((oc[2] & 0x03) << 4);
			p[2] = _NXT | (oc[2] >> 2);
			p[1] = _NXT | (oc[3] & 0x3f);
			p[0] = _SEQ6 | ((oc[3] & 0x40) >> 6);
			break;
		}

		/*
		 * NOTE: do not check here for forbidden UTF-8 characters.
		 * They cannot appear here because we do proper conversion.
		 */

		p += n;
	}

	return total;
}