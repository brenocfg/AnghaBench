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
typedef  int (* mbverifier ) (unsigned char const*,int) ;
struct TYPE_2__ {int (* mbverify ) (unsigned char const*,int) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  Assert (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  IS_HIGHBIT_SET (char const) ; 
 int /*<<< orphan*/  PG_VALID_ENCODING (int) ; 
 char* memchr (char const*,int /*<<< orphan*/ ,int) ; 
 int pg_encoding_max_length (int) ; 
 TYPE_1__* pg_wchar_table ; 
 int /*<<< orphan*/  report_invalid_encoding (int,char const*,int) ; 
 int stub1 (unsigned char const*,int) ; 

int
pg_verify_mbstr_len(int encoding, const char *mbstr, int len, bool noError)
{
	mbverifier	mbverify;
	int			mb_len;

	Assert(PG_VALID_ENCODING(encoding));

	/*
	 * In single-byte encodings, we need only reject nulls (\0).
	 */
	if (pg_encoding_max_length(encoding) <= 1)
	{
		const char *nullpos = memchr(mbstr, 0, len);

		if (nullpos == NULL)
			return len;
		if (noError)
			return -1;
		report_invalid_encoding(encoding, nullpos, 1);
	}

	/* fetch function pointer just once */
	mbverify = pg_wchar_table[encoding].mbverify;

	mb_len = 0;

	while (len > 0)
	{
		int			l;

		/* fast path for ASCII-subset characters */
		if (!IS_HIGHBIT_SET(*mbstr))
		{
			if (*mbstr != '\0')
			{
				mb_len++;
				mbstr++;
				len--;
				continue;
			}
			if (noError)
				return -1;
			report_invalid_encoding(encoding, mbstr, len);
		}

		l = (*mbverify) ((const unsigned char *) mbstr, len);

		if (l < 0)
		{
			if (noError)
				return -1;
			report_invalid_encoding(encoding, mbstr, len);
		}

		mbstr += l;
		len -= l;
		mb_len++;
	}
	return mb_len;
}