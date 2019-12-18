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
 int PQdsplen (char const*,int) ; 
 int PQmblen (char const*,int) ; 

void
pg_wcssize(const unsigned char *pwcs, size_t len, int encoding,
		   int *result_width, int *result_height, int *result_format_size)
{
	int			w,
				chlen = 0,
				linewidth = 0;
	int			width = 0;
	int			height = 1;
	int			format_size = 0;

	for (; *pwcs && len > 0; pwcs += chlen)
	{
		chlen = PQmblen((const char *) pwcs, encoding);
		if (len < (size_t) chlen)
			break;
		w = PQdsplen((const char *) pwcs, encoding);

		if (chlen == 1)			/* single-byte char */
		{
			if (*pwcs == '\n')	/* Newline */
			{
				if (linewidth > width)
					width = linewidth;
				linewidth = 0;
				height += 1;
				format_size += 1;	/* For NUL char */
			}
			else if (*pwcs == '\r') /* Linefeed */
			{
				linewidth += 2;
				format_size += 2;
			}
			else if (*pwcs == '\t') /* Tab */
			{
				do
				{
					linewidth++;
					format_size++;
				} while (linewidth % 8 != 0);
			}
			else if (w < 0)		/* Other control char */
			{
				linewidth += 4;
				format_size += 4;
			}
			else				/* Output it as-is */
			{
				linewidth += w;
				format_size += 1;
			}
		}
		else if (w < 0)			/* Non-ascii control char */
		{
			linewidth += 6;		/* \u0000 */
			format_size += 6;
		}
		else					/* All other chars */
		{
			linewidth += w;
			format_size += chlen;
		}
		len -= chlen;
	}
	if (linewidth > width)
		width = linewidth;
	format_size += 1;			/* For NUL char */

	/* Set results */
	if (result_width)
		*result_width = width;
	if (result_height)
		*result_height = height;
	if (result_format_size)
		*result_format_size = format_size;
}