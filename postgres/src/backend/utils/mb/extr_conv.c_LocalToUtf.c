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
typedef  unsigned char (* utf_local_conversion_func ) (unsigned char) ;
typedef  unsigned char uint32 ;
typedef  int /*<<< orphan*/  pg_mb_radix_tree ;
struct TYPE_5__ {unsigned char utf1; unsigned char utf2; } ;
typedef  TYPE_1__ pg_local_to_utf_combined ;

/* Variables and functions */
 int /*<<< orphan*/  ERRCODE_INVALID_PARAMETER_VALUE ; 
 int /*<<< orphan*/  ERROR ; 
 int /*<<< orphan*/  IS_HIGHBIT_SET (unsigned char const) ; 
 int /*<<< orphan*/  PG_UTF8 ; 
 int /*<<< orphan*/  PG_VALID_ENCODING (int) ; 
 TYPE_1__* bsearch (unsigned char*,TYPE_1__ const*,int,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  compare4 ; 
 int /*<<< orphan*/  elog (int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  ereport (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  errcode (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  errmsg (char*,int) ; 
 int pg_encoding_verifymb (int,char const*,int) ; 
 unsigned char pg_mb_radix_conv (int /*<<< orphan*/  const*,int,unsigned char,unsigned char,unsigned char,unsigned char) ; 
 int /*<<< orphan*/  report_invalid_encoding (int,char const*,int) ; 
 int /*<<< orphan*/  report_untranslatable_char (int,int /*<<< orphan*/ ,char const*,int) ; 
 unsigned char* store_coded_char (unsigned char*,unsigned char) ; 
 unsigned char stub1 (unsigned char) ; 

void
LocalToUtf(const unsigned char *iso, int len,
		   unsigned char *utf,
		   const pg_mb_radix_tree *map,
		   const pg_local_to_utf_combined *cmap, int cmapsize,
		   utf_local_conversion_func conv_func,
		   int encoding)
{
	uint32		iiso;
	int			l;
	const pg_local_to_utf_combined *cp;

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
		if (*iso == '\0')
			break;

		if (!IS_HIGHBIT_SET(*iso))
		{
			/* ASCII case is easy, assume it's one-to-one conversion */
			*utf++ = *iso++;
			l = 1;
			continue;
		}

		l = pg_encoding_verifymb(encoding, (const char *) iso, len);
		if (l < 0)
			break;

		/* collect coded char of length l */
		if (l == 1)
			b4 = *iso++;
		else if (l == 2)
		{
			b3 = *iso++;
			b4 = *iso++;
		}
		else if (l == 3)
		{
			b2 = *iso++;
			b3 = *iso++;
			b4 = *iso++;
		}
		else if (l == 4)
		{
			b1 = *iso++;
			b2 = *iso++;
			b3 = *iso++;
			b4 = *iso++;
		}
		else
		{
			elog(ERROR, "unsupported character length %d", l);
			iiso = 0;			/* keep compiler quiet */
		}
		iiso = (b1 << 24 | b2 << 16 | b3 << 8 | b4);

		if (map)
		{
			uint32		converted = pg_mb_radix_conv(map, l, b1, b2, b3, b4);

			if (converted)
			{
				utf = store_coded_char(utf, converted);
				continue;
			}

			/* If there's a combined character map, try that */
			if (cmap)
			{
				cp = bsearch(&iiso, cmap, cmapsize,
							 sizeof(pg_local_to_utf_combined), compare4);

				if (cp)
				{
					utf = store_coded_char(utf, cp->utf1);
					utf = store_coded_char(utf, cp->utf2);
					continue;
				}
			}
		}

		/* if there's a conversion function, try that */
		if (conv_func)
		{
			uint32		converted = (*conv_func) (iiso);

			if (converted)
			{
				utf = store_coded_char(utf, converted);
				continue;
			}
		}

		/* failed to translate this character */
		report_untranslatable_char(encoding, PG_UTF8,
								   (const char *) (iso - l), len);
	}

	/* if we broke out of loop early, must be invalid input */
	if (len > 0)
		report_invalid_encoding(encoding, (const char *) iso, len);

	*utf = '\0';
}