#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int (* mblen_converter ) (unsigned char const*) ;
struct TYPE_2__ {int (* mblen ) (unsigned char const*) ;} ;

/* Variables and functions */
 int cliplen (char const*,int,int) ; 
 int pg_encoding_max_length (int) ; 
 TYPE_1__* pg_wchar_table ; 
 int stub1 (unsigned char const*) ; 

int
pg_encoding_mbcliplen(int encoding, const char *mbstr,
					  int len, int limit)
{
	mblen_converter mblen_fn;
	int			clen = 0;
	int			l;

	/* optimization for single byte encoding */
	if (pg_encoding_max_length(encoding) == 1)
		return cliplen(mbstr, len, limit);

	mblen_fn = pg_wchar_table[encoding].mblen;

	while (len > 0 && *mbstr)
	{
		l = (*mblen_fn) ((const unsigned char *) mbstr);
		if ((clen + l) > limit)
			break;
		clen += l;
		if (clen == limit)
			break;
		len -= l;
		mbstr += l;
	}
	return clen;
}