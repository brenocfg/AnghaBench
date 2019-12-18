#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int (* utf_local_conversion_func ) (int) ;
typedef  int uint32 ;
struct TYPE_5__ {int code; } ;
typedef  TYPE_1__ pg_utf_to_local_combined ;
typedef  int /*<<< orphan*/  pg_mb_radix_tree ;

/* Variables and functions */
 int /*<<< orphan*/  ERRCODE_INVALID_PARAMETER_VALUE ; 
 int /*<<< orphan*/  ERROR ; 
 int /*<<< orphan*/  PG_UTF8 ; 
 int /*<<< orphan*/  PG_VALID_ENCODING (int) ; 
 TYPE_1__* bsearch (int*,TYPE_1__ const*,int,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  compare3 ; 
 int /*<<< orphan*/  elog (int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  ereport (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  errcode (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  errmsg (char*,int) ; 
 int pg_mb_radix_conv (int /*<<< orphan*/  const*,int,unsigned char,unsigned char,unsigned char,unsigned char) ; 
 int /*<<< orphan*/  pg_utf8_islegal (unsigned char const*,int) ; 
 int pg_utf_mblen (unsigned char const*) ; 
 int /*<<< orphan*/  report_invalid_encoding (int /*<<< orphan*/ ,char const*,int) ; 
 int /*<<< orphan*/  report_untranslatable_char (int /*<<< orphan*/ ,int,char const*,int) ; 
 unsigned char* store_coded_char (unsigned char*,int) ; 
 int stub1 (int) ; 

void
UtfToLocal(const unsigned char *utf, int len,
		   unsigned char *iso,
		   const pg_mb_radix_tree *map,
		   const pg_utf_to_local_combined *cmap, int cmapsize,
		   utf_local_conversion_func conv_func,
		   int encoding)
{
	uint32		iutf;
	int			l;
	const pg_utf_to_local_combined *cp;

	if (!PG_VALID_ENCODING(encoding))
		ereport(ERROR,
				(errcode(ERRCODE_INVALID_PARAMETER_VALUE),
				 errmsg("invalid encoding number: %d", encoding)));

	for (; len > 0; len -= l)
	{
		unsigned char b1 = 0;
		unsigned char b2 = 0;
		unsigned char b3 = 0;
		unsigned char b4 = 0;

		/* "break" cases all represent errors */
		if (*utf == '\0')
			break;

		l = pg_utf_mblen(utf);
		if (len < l)
			break;

		if (!pg_utf8_islegal(utf, l))
			break;

		if (l == 1)
		{
			/* ASCII case is easy, assume it's one-to-one conversion */
			*iso++ = *utf++;
			continue;
		}

		/* collect coded char of length l */
		if (l == 2)
		{
			b3 = *utf++;
			b4 = *utf++;
		}
		else if (l == 3)
		{
			b2 = *utf++;
			b3 = *utf++;
			b4 = *utf++;
		}
		else if (l == 4)
		{
			b1 = *utf++;
			b2 = *utf++;
			b3 = *utf++;
			b4 = *utf++;
		}
		else
		{
			elog(ERROR, "unsupported character length %d", l);
			iutf = 0;			/* keep compiler quiet */
		}
		iutf = (b1 << 24 | b2 << 16 | b3 << 8 | b4);

		/* First, try with combined map if possible */
		if (cmap && len > l)
		{
			const unsigned char *utf_save = utf;
			int			len_save = len;
			int			l_save = l;

			/* collect next character, same as above */
			len -= l;

			l = pg_utf_mblen(utf);
			if (len < l)
				break;

			if (!pg_utf8_islegal(utf, l))
				break;

			/* We assume ASCII character cannot be in combined map */
			if (l > 1)
			{
				uint32		iutf2;
				uint32		cutf[2];

				if (l == 2)
				{
					iutf2 = *utf++ << 8;
					iutf2 |= *utf++;
				}
				else if (l == 3)
				{
					iutf2 = *utf++ << 16;
					iutf2 |= *utf++ << 8;
					iutf2 |= *utf++;
				}
				else if (l == 4)
				{
					iutf2 = *utf++ << 24;
					iutf2 |= *utf++ << 16;
					iutf2 |= *utf++ << 8;
					iutf2 |= *utf++;
				}
				else
				{
					elog(ERROR, "unsupported character length %d", l);
					iutf2 = 0;	/* keep compiler quiet */
				}

				cutf[0] = iutf;
				cutf[1] = iutf2;

				cp = bsearch(cutf, cmap, cmapsize,
							 sizeof(pg_utf_to_local_combined), compare3);

				if (cp)
				{
					iso = store_coded_char(iso, cp->code);
					continue;
				}
			}

			/* fail, so back up to reprocess second character next time */
			utf = utf_save;
			len = len_save;
			l = l_save;
		}

		/* Now check ordinary map */
		if (map)
		{
			uint32		converted = pg_mb_radix_conv(map, l, b1, b2, b3, b4);

			if (converted)
			{
				iso = store_coded_char(iso, converted);
				continue;
			}
		}

		/* if there's a conversion function, try that */
		if (conv_func)
		{
			uint32		converted = (*conv_func) (iutf);

			if (converted)
			{
				iso = store_coded_char(iso, converted);
				continue;
			}
		}

		/* failed to translate this character */
		report_untranslatable_char(PG_UTF8, encoding,
								   (const char *) (utf - l), len);
	}

	/* if we broke out of loop early, must be invalid input */
	if (len > 0)
		report_invalid_encoding(PG_UTF8, (const char *) utf, len);

	*iso = '\0';
}