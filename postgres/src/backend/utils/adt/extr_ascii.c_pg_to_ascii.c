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
 int /*<<< orphan*/  ERRCODE_FEATURE_NOT_SUPPORTED ; 
 int /*<<< orphan*/  ERROR ; 
 int PG_LATIN1 ; 
 int PG_LATIN2 ; 
 int PG_LATIN9 ; 
 int PG_WIN1250 ; 
 int RANGE_128 ; 
 int RANGE_160 ; 
 int /*<<< orphan*/  ereport (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  errcode (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  errmsg (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pg_encoding_to_char (int) ; 

__attribute__((used)) static void
pg_to_ascii(unsigned char *src, unsigned char *src_end, unsigned char *dest, int enc)
{
	unsigned char *x;
	const unsigned char *ascii;
	int			range;

	/*
	 * relevant start for an encoding
	 */
#define RANGE_128	128
#define RANGE_160	160

	if (enc == PG_LATIN1)
	{
		/*
		 * ISO-8859-1 <range: 160 -- 255>
		 */
		ascii = (const unsigned char *) "  cL Y  \"Ca  -R     'u .,      ?AAAAAAACEEEEIIII NOOOOOxOUUUUYTBaaaaaaaceeeeiiii nooooo/ouuuuyty";
		range = RANGE_160;
	}
	else if (enc == PG_LATIN2)
	{
		/*
		 * ISO-8859-2 <range: 160 -- 255>
		 */
		ascii = (const unsigned char *) " A L LS \"SSTZ-ZZ a,l'ls ,sstz\"zzRAAAALCCCEEEEIIDDNNOOOOxRUUUUYTBraaaalccceeeeiiddnnoooo/ruuuuyt.";
		range = RANGE_160;
	}
	else if (enc == PG_LATIN9)
	{
		/*
		 * ISO-8859-15 <range: 160 -- 255>
		 */
		ascii = (const unsigned char *) "  cL YS sCa  -R     Zu .z   EeY?AAAAAAACEEEEIIII NOOOOOxOUUUUYTBaaaaaaaceeeeiiii nooooo/ouuuuyty";
		range = RANGE_160;
	}
	else if (enc == PG_WIN1250)
	{
		/*
		 * Window CP1250 <range: 128 -- 255>
		 */
		ascii = (const unsigned char *) "  ' \"    %S<STZZ `'\"\".--  s>stzz   L A  \"CS  -RZ  ,l'u .,as L\"lzRAAAALCCCEEEEIIDDNNOOOOxRUUUUYTBraaaalccceeeeiiddnnoooo/ruuuuyt ";
		range = RANGE_128;
	}
	else
	{
		ereport(ERROR,
				(errcode(ERRCODE_FEATURE_NOT_SUPPORTED),
				 errmsg("encoding conversion from %s to ASCII not supported",
						pg_encoding_to_char(enc))));
		return;					/* keep compiler quiet */
	}

	/*
	 * Encode
	 */
	for (x = src; x < src_end; x++)
	{
		if (*x < 128)
			*dest++ = *x;
		else if (*x < range)
			*dest++ = ' ';		/* bogus 128 to 'range' */
		else
			*dest++ = ascii[*x - range];
	}
}