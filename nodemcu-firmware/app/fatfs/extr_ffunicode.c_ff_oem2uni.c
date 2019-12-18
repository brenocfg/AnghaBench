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
typedef  scalar_t__ WORD ;
typedef  int WCHAR ;
typedef  int UINT ;

/* Variables and functions */
 int* CVTBL (int /*<<< orphan*/ ,scalar_t__) ; 
 scalar_t__ FF_CODE_PAGE ; 
 int /*<<< orphan*/  oem2uni ; 

WCHAR ff_oem2uni (	/* Returns Unicode character, zero on error */
	WCHAR	oem,	/* OEM code to be converted */
	WORD	cp		/* Code page for the conversion */
)
{
	const WCHAR *p;
	WCHAR c = 0;
	UINT i = 0, n, li, hi;


	if (oem < 0x80) {	/* ASCII? */
		c = oem;

	} else {			/* Extended char */
		if (cp == FF_CODE_PAGE) {	/* Is it valid code page? */
			p = CVTBL(oem2uni, FF_CODE_PAGE);
			hi = sizeof CVTBL(oem2uni, FF_CODE_PAGE) / 4 - 1;
			li = 0;
			for (n = 16; n; n--) {
				i = li + (hi - li) / 2;
				if (oem == p[i * 2]) break;
				if (oem > p[i * 2]) {
					li = i;
				} else {
					hi = i;
				}
			}
			if (n != 0) c = p[i * 2 + 1];
		}
	}

	return c;
}