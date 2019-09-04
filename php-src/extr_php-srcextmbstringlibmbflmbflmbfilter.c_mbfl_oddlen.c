#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {unsigned char* val; size_t len; TYPE_2__* encoding; } ;
typedef  TYPE_1__ mbfl_string ;
struct TYPE_5__ {int flag; unsigned char* mblen_table; } ;
typedef  TYPE_2__ mbfl_encoding ;

/* Variables and functions */
 int MBFL_ENCTYPE_SBCS ; 
 int MBFL_ENCTYPE_WCS2BE ; 
 int MBFL_ENCTYPE_WCS2LE ; 
 int MBFL_ENCTYPE_WCS4BE ; 
 int MBFL_ENCTYPE_WCS4LE ; 

size_t
mbfl_oddlen(mbfl_string *string)
{
	size_t len, n, k;
	unsigned char *p;
	const mbfl_encoding *encoding = string->encoding;

	len = 0;
	if (encoding->flag & MBFL_ENCTYPE_SBCS) {
		return 0;
	} else if (encoding->flag & (MBFL_ENCTYPE_WCS2BE | MBFL_ENCTYPE_WCS2LE)) {
		return len % 2;
	} else if (encoding->flag & (MBFL_ENCTYPE_WCS4BE | MBFL_ENCTYPE_WCS4LE)) {
		return len % 4;
	} else if (encoding->mblen_table != NULL) {
		const unsigned char *mbtab = encoding->mblen_table;
 		n = 0;
		p = string->val;
		k = string->len;
		/* count */
		if (p != NULL) {
			while (n < k) {
				unsigned m = mbtab[*p];
				n += m;
				p += m;
			};
		}
		return n-k;
	} else {
		/* how can i do ? */
		return 0;
	}
	/* NOT REACHED */
}