#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {char* p; } ;
typedef  TYPE_1__* STREAM ;

/* Variables and functions */

void
rdp_out_unistr(STREAM s, char *string, int len)
{
	if (string == NULL || len == 0)
		return;

#ifdef HAVE_ICONV
	size_t ibl = strlen(string), obl = len + 2;
	static iconv_t iconv_h = (iconv_t) - 1;
	char *pin = string, *pout = (char *) s->p;

	memset(pout, 0, len + 4);

	if (g_iconv_works)
	{
		if (iconv_h == (iconv_t) - 1)
		{
			size_t i = 1, o = 4;
			if ((iconv_h = iconv_open(WINDOWS_CODEPAGE, g_codepage)) == (iconv_t) - 1)
			{
				warning("rdp_out_unistr: iconv_open[%s -> %s] fail %d\n",
					g_codepage, WINDOWS_CODEPAGE, (int) iconv_h);

				g_iconv_works = False;
				rdp_out_unistr(s, string, len);
				return;
			}
			if (iconv(iconv_h, (ICONV_CONST char **) &pin, &i, &pout, &o) ==
			    (size_t) - 1)
			{
				iconv_close(iconv_h);
				iconv_h = (iconv_t) - 1;
				warning("rdp_out_unistr: iconv(1) fail, errno %d\n", errno);

				g_iconv_works = False;
				rdp_out_unistr(s, string, len);
				return;
			}
			pin = string;
			pout = (char *) s->p;
		}

		if (iconv(iconv_h, (ICONV_CONST char **) &pin, &ibl, &pout, &obl) == (size_t) - 1)
		{
			iconv_close(iconv_h);
			iconv_h = (iconv_t) - 1;
			warning("rdp_out_unistr: iconv(2) fail, errno %d\n", errno);

			g_iconv_works = False;
			rdp_out_unistr(s, string, len);
			return;
		}

		s->p += len + 2;

	}
	else
#endif
	{
		int i = 0, j = 0;

		len += 2;

		while (i < len)
		{
			s->p[i++] = string[j++];
			s->p[i++] = 0;
		}

		s->p += len;
	}
}