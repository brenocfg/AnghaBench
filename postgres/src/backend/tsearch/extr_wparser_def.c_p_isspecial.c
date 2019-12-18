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
typedef  int pg_wchar ;
struct TYPE_5__ {int* pgwstr; TYPE_1__* state; scalar_t__* wstr; scalar_t__ usewide; scalar_t__ str; } ;
struct TYPE_4__ {int poschar; scalar_t__ posbyte; } ;
typedef  TYPE_2__ TParser ;

/* Variables and functions */
 scalar_t__ GetDatabaseEncoding () ; 
 scalar_t__ PG_UTF8 ; 
 int lengthof (int const*) ; 
 scalar_t__ pg_dsplen (scalar_t__) ; 

__attribute__((used)) static int
p_isspecial(TParser *prs)
{
	/*
	 * pg_dsplen could return -1 which means error or control character
	 */
	if (pg_dsplen(prs->str + prs->state->posbyte) == 0)
		return 1;

	/*
	 * Unicode Characters in the 'Mark, Spacing Combining' Category That
	 * characters are not alpha although they are not breakers of word too.
	 * Check that only in utf encoding, because other encodings aren't
	 * supported by postgres or even exists.
	 */
	if (GetDatabaseEncoding() == PG_UTF8 && prs->usewide)
	{
		static const pg_wchar strange_letter[] = {
			/*
			 * use binary search, so elements should be ordered
			 */
			0x0903,				/* DEVANAGARI SIGN VISARGA */
			0x093E,				/* DEVANAGARI VOWEL SIGN AA */
			0x093F,				/* DEVANAGARI VOWEL SIGN I */
			0x0940,				/* DEVANAGARI VOWEL SIGN II */
			0x0949,				/* DEVANAGARI VOWEL SIGN CANDRA O */
			0x094A,				/* DEVANAGARI VOWEL SIGN SHORT O */
			0x094B,				/* DEVANAGARI VOWEL SIGN O */
			0x094C,				/* DEVANAGARI VOWEL SIGN AU */
			0x0982,				/* BENGALI SIGN ANUSVARA */
			0x0983,				/* BENGALI SIGN VISARGA */
			0x09BE,				/* BENGALI VOWEL SIGN AA */
			0x09BF,				/* BENGALI VOWEL SIGN I */
			0x09C0,				/* BENGALI VOWEL SIGN II */
			0x09C7,				/* BENGALI VOWEL SIGN E */
			0x09C8,				/* BENGALI VOWEL SIGN AI */
			0x09CB,				/* BENGALI VOWEL SIGN O */
			0x09CC,				/* BENGALI VOWEL SIGN AU */
			0x09D7,				/* BENGALI AU LENGTH MARK */
			0x0A03,				/* GURMUKHI SIGN VISARGA */
			0x0A3E,				/* GURMUKHI VOWEL SIGN AA */
			0x0A3F,				/* GURMUKHI VOWEL SIGN I */
			0x0A40,				/* GURMUKHI VOWEL SIGN II */
			0x0A83,				/* GUJARATI SIGN VISARGA */
			0x0ABE,				/* GUJARATI VOWEL SIGN AA */
			0x0ABF,				/* GUJARATI VOWEL SIGN I */
			0x0AC0,				/* GUJARATI VOWEL SIGN II */
			0x0AC9,				/* GUJARATI VOWEL SIGN CANDRA O */
			0x0ACB,				/* GUJARATI VOWEL SIGN O */
			0x0ACC,				/* GUJARATI VOWEL SIGN AU */
			0x0B02,				/* ORIYA SIGN ANUSVARA */
			0x0B03,				/* ORIYA SIGN VISARGA */
			0x0B3E,				/* ORIYA VOWEL SIGN AA */
			0x0B40,				/* ORIYA VOWEL SIGN II */
			0x0B47,				/* ORIYA VOWEL SIGN E */
			0x0B48,				/* ORIYA VOWEL SIGN AI */
			0x0B4B,				/* ORIYA VOWEL SIGN O */
			0x0B4C,				/* ORIYA VOWEL SIGN AU */
			0x0B57,				/* ORIYA AU LENGTH MARK */
			0x0BBE,				/* TAMIL VOWEL SIGN AA */
			0x0BBF,				/* TAMIL VOWEL SIGN I */
			0x0BC1,				/* TAMIL VOWEL SIGN U */
			0x0BC2,				/* TAMIL VOWEL SIGN UU */
			0x0BC6,				/* TAMIL VOWEL SIGN E */
			0x0BC7,				/* TAMIL VOWEL SIGN EE */
			0x0BC8,				/* TAMIL VOWEL SIGN AI */
			0x0BCA,				/* TAMIL VOWEL SIGN O */
			0x0BCB,				/* TAMIL VOWEL SIGN OO */
			0x0BCC,				/* TAMIL VOWEL SIGN AU */
			0x0BD7,				/* TAMIL AU LENGTH MARK */
			0x0C01,				/* TELUGU SIGN CANDRABINDU */
			0x0C02,				/* TELUGU SIGN ANUSVARA */
			0x0C03,				/* TELUGU SIGN VISARGA */
			0x0C41,				/* TELUGU VOWEL SIGN U */
			0x0C42,				/* TELUGU VOWEL SIGN UU */
			0x0C43,				/* TELUGU VOWEL SIGN VOCALIC R */
			0x0C44,				/* TELUGU VOWEL SIGN VOCALIC RR */
			0x0C82,				/* KANNADA SIGN ANUSVARA */
			0x0C83,				/* KANNADA SIGN VISARGA */
			0x0CBE,				/* KANNADA VOWEL SIGN AA */
			0x0CC0,				/* KANNADA VOWEL SIGN II */
			0x0CC1,				/* KANNADA VOWEL SIGN U */
			0x0CC2,				/* KANNADA VOWEL SIGN UU */
			0x0CC3,				/* KANNADA VOWEL SIGN VOCALIC R */
			0x0CC4,				/* KANNADA VOWEL SIGN VOCALIC RR */
			0x0CC7,				/* KANNADA VOWEL SIGN EE */
			0x0CC8,				/* KANNADA VOWEL SIGN AI */
			0x0CCA,				/* KANNADA VOWEL SIGN O */
			0x0CCB,				/* KANNADA VOWEL SIGN OO */
			0x0CD5,				/* KANNADA LENGTH MARK */
			0x0CD6,				/* KANNADA AI LENGTH MARK */
			0x0D02,				/* MALAYALAM SIGN ANUSVARA */
			0x0D03,				/* MALAYALAM SIGN VISARGA */
			0x0D3E,				/* MALAYALAM VOWEL SIGN AA */
			0x0D3F,				/* MALAYALAM VOWEL SIGN I */
			0x0D40,				/* MALAYALAM VOWEL SIGN II */
			0x0D46,				/* MALAYALAM VOWEL SIGN E */
			0x0D47,				/* MALAYALAM VOWEL SIGN EE */
			0x0D48,				/* MALAYALAM VOWEL SIGN AI */
			0x0D4A,				/* MALAYALAM VOWEL SIGN O */
			0x0D4B,				/* MALAYALAM VOWEL SIGN OO */
			0x0D4C,				/* MALAYALAM VOWEL SIGN AU */
			0x0D57,				/* MALAYALAM AU LENGTH MARK */
			0x0D82,				/* SINHALA SIGN ANUSVARAYA */
			0x0D83,				/* SINHALA SIGN VISARGAYA */
			0x0DCF,				/* SINHALA VOWEL SIGN AELA-PILLA */
			0x0DD0,				/* SINHALA VOWEL SIGN KETTI AEDA-PILLA */
			0x0DD1,				/* SINHALA VOWEL SIGN DIGA AEDA-PILLA */
			0x0DD8,				/* SINHALA VOWEL SIGN GAETTA-PILLA */
			0x0DD9,				/* SINHALA VOWEL SIGN KOMBUVA */
			0x0DDA,				/* SINHALA VOWEL SIGN DIGA KOMBUVA */
			0x0DDB,				/* SINHALA VOWEL SIGN KOMBU DEKA */
			0x0DDC,				/* SINHALA VOWEL SIGN KOMBUVA HAA AELA-PILLA */
			0x0DDD,				/* SINHALA VOWEL SIGN KOMBUVA HAA DIGA
								 * AELA-PILLA */
			0x0DDE,				/* SINHALA VOWEL SIGN KOMBUVA HAA GAYANUKITTA */
			0x0DDF,				/* SINHALA VOWEL SIGN GAYANUKITTA */
			0x0DF2,				/* SINHALA VOWEL SIGN DIGA GAETTA-PILLA */
			0x0DF3,				/* SINHALA VOWEL SIGN DIGA GAYANUKITTA */
			0x0F3E,				/* TIBETAN SIGN YAR TSHES */
			0x0F3F,				/* TIBETAN SIGN MAR TSHES */
			0x0F7F,				/* TIBETAN SIGN RNAM BCAD */
			0x102B,				/* MYANMAR VOWEL SIGN TALL AA */
			0x102C,				/* MYANMAR VOWEL SIGN AA */
			0x1031,				/* MYANMAR VOWEL SIGN E */
			0x1038,				/* MYANMAR SIGN VISARGA */
			0x103B,				/* MYANMAR CONSONANT SIGN MEDIAL YA */
			0x103C,				/* MYANMAR CONSONANT SIGN MEDIAL RA */
			0x1056,				/* MYANMAR VOWEL SIGN VOCALIC R */
			0x1057,				/* MYANMAR VOWEL SIGN VOCALIC RR */
			0x1062,				/* MYANMAR VOWEL SIGN SGAW KAREN EU */
			0x1063,				/* MYANMAR TONE MARK SGAW KAREN HATHI */
			0x1064,				/* MYANMAR TONE MARK SGAW KAREN KE PHO */
			0x1067,				/* MYANMAR VOWEL SIGN WESTERN PWO KAREN EU */
			0x1068,				/* MYANMAR VOWEL SIGN WESTERN PWO KAREN UE */
			0x1069,				/* MYANMAR SIGN WESTERN PWO KAREN TONE-1 */
			0x106A,				/* MYANMAR SIGN WESTERN PWO KAREN TONE-2 */
			0x106B,				/* MYANMAR SIGN WESTERN PWO KAREN TONE-3 */
			0x106C,				/* MYANMAR SIGN WESTERN PWO KAREN TONE-4 */
			0x106D,				/* MYANMAR SIGN WESTERN PWO KAREN TONE-5 */
			0x1083,				/* MYANMAR VOWEL SIGN SHAN AA */
			0x1084,				/* MYANMAR VOWEL SIGN SHAN E */
			0x1087,				/* MYANMAR SIGN SHAN TONE-2 */
			0x1088,				/* MYANMAR SIGN SHAN TONE-3 */
			0x1089,				/* MYANMAR SIGN SHAN TONE-5 */
			0x108A,				/* MYANMAR SIGN SHAN TONE-6 */
			0x108B,				/* MYANMAR SIGN SHAN COUNCIL TONE-2 */
			0x108C,				/* MYANMAR SIGN SHAN COUNCIL TONE-3 */
			0x108F,				/* MYANMAR SIGN RUMAI PALAUNG TONE-5 */
			0x17B6,				/* KHMER VOWEL SIGN AA */
			0x17BE,				/* KHMER VOWEL SIGN OE */
			0x17BF,				/* KHMER VOWEL SIGN YA */
			0x17C0,				/* KHMER VOWEL SIGN IE */
			0x17C1,				/* KHMER VOWEL SIGN E */
			0x17C2,				/* KHMER VOWEL SIGN AE */
			0x17C3,				/* KHMER VOWEL SIGN AI */
			0x17C4,				/* KHMER VOWEL SIGN OO */
			0x17C5,				/* KHMER VOWEL SIGN AU */
			0x17C7,				/* KHMER SIGN REAHMUK */
			0x17C8,				/* KHMER SIGN YUUKALEAPINTU */
			0x1923,				/* LIMBU VOWEL SIGN EE */
			0x1924,				/* LIMBU VOWEL SIGN AI */
			0x1925,				/* LIMBU VOWEL SIGN OO */
			0x1926,				/* LIMBU VOWEL SIGN AU */
			0x1929,				/* LIMBU SUBJOINED LETTER YA */
			0x192A,				/* LIMBU SUBJOINED LETTER RA */
			0x192B,				/* LIMBU SUBJOINED LETTER WA */
			0x1930,				/* LIMBU SMALL LETTER KA */
			0x1931,				/* LIMBU SMALL LETTER NGA */
			0x1933,				/* LIMBU SMALL LETTER TA */
			0x1934,				/* LIMBU SMALL LETTER NA */
			0x1935,				/* LIMBU SMALL LETTER PA */
			0x1936,				/* LIMBU SMALL LETTER MA */
			0x1937,				/* LIMBU SMALL LETTER RA */
			0x1938,				/* LIMBU SMALL LETTER LA */
			0x19B0,				/* NEW TAI LUE VOWEL SIGN VOWEL SHORTENER */
			0x19B1,				/* NEW TAI LUE VOWEL SIGN AA */
			0x19B2,				/* NEW TAI LUE VOWEL SIGN II */
			0x19B3,				/* NEW TAI LUE VOWEL SIGN U */
			0x19B4,				/* NEW TAI LUE VOWEL SIGN UU */
			0x19B5,				/* NEW TAI LUE VOWEL SIGN E */
			0x19B6,				/* NEW TAI LUE VOWEL SIGN AE */
			0x19B7,				/* NEW TAI LUE VOWEL SIGN O */
			0x19B8,				/* NEW TAI LUE VOWEL SIGN OA */
			0x19B9,				/* NEW TAI LUE VOWEL SIGN UE */
			0x19BA,				/* NEW TAI LUE VOWEL SIGN AY */
			0x19BB,				/* NEW TAI LUE VOWEL SIGN AAY */
			0x19BC,				/* NEW TAI LUE VOWEL SIGN UY */
			0x19BD,				/* NEW TAI LUE VOWEL SIGN OY */
			0x19BE,				/* NEW TAI LUE VOWEL SIGN OAY */
			0x19BF,				/* NEW TAI LUE VOWEL SIGN UEY */
			0x19C0,				/* NEW TAI LUE VOWEL SIGN IY */
			0x19C8,				/* NEW TAI LUE TONE MARK-1 */
			0x19C9,				/* NEW TAI LUE TONE MARK-2 */
			0x1A19,				/* BUGINESE VOWEL SIGN E */
			0x1A1A,				/* BUGINESE VOWEL SIGN O */
			0x1A1B,				/* BUGINESE VOWEL SIGN AE */
			0x1B04,				/* BALINESE SIGN BISAH */
			0x1B35,				/* BALINESE VOWEL SIGN TEDUNG */
			0x1B3B,				/* BALINESE VOWEL SIGN RA REPA TEDUNG */
			0x1B3D,				/* BALINESE VOWEL SIGN LA LENGA TEDUNG */
			0x1B3E,				/* BALINESE VOWEL SIGN TALING */
			0x1B3F,				/* BALINESE VOWEL SIGN TALING REPA */
			0x1B40,				/* BALINESE VOWEL SIGN TALING TEDUNG */
			0x1B41,				/* BALINESE VOWEL SIGN TALING REPA TEDUNG */
			0x1B43,				/* BALINESE VOWEL SIGN PEPET TEDUNG */
			0x1B44,				/* BALINESE ADEG ADEG */
			0x1B82,				/* SUNDANESE SIGN PANGWISAD */
			0x1BA1,				/* SUNDANESE CONSONANT SIGN PAMINGKAL */
			0x1BA6,				/* SUNDANESE VOWEL SIGN PANAELAENG */
			0x1BA7,				/* SUNDANESE VOWEL SIGN PANOLONG */
			0x1BAA,				/* SUNDANESE SIGN PAMAAEH */
			0x1C24,				/* LEPCHA SUBJOINED LETTER YA */
			0x1C25,				/* LEPCHA SUBJOINED LETTER RA */
			0x1C26,				/* LEPCHA VOWEL SIGN AA */
			0x1C27,				/* LEPCHA VOWEL SIGN I */
			0x1C28,				/* LEPCHA VOWEL SIGN O */
			0x1C29,				/* LEPCHA VOWEL SIGN OO */
			0x1C2A,				/* LEPCHA VOWEL SIGN U */
			0x1C2B,				/* LEPCHA VOWEL SIGN UU */
			0x1C34,				/* LEPCHA CONSONANT SIGN NYIN-DO */
			0x1C35,				/* LEPCHA CONSONANT SIGN KANG */
			0xA823,				/* SYLOTI NAGRI VOWEL SIGN A */
			0xA824,				/* SYLOTI NAGRI VOWEL SIGN I */
			0xA827,				/* SYLOTI NAGRI VOWEL SIGN OO */
			0xA880,				/* SAURASHTRA SIGN ANUSVARA */
			0xA881,				/* SAURASHTRA SIGN VISARGA */
			0xA8B4,				/* SAURASHTRA CONSONANT SIGN HAARU */
			0xA8B5,				/* SAURASHTRA VOWEL SIGN AA */
			0xA8B6,				/* SAURASHTRA VOWEL SIGN I */
			0xA8B7,				/* SAURASHTRA VOWEL SIGN II */
			0xA8B8,				/* SAURASHTRA VOWEL SIGN U */
			0xA8B9,				/* SAURASHTRA VOWEL SIGN UU */
			0xA8BA,				/* SAURASHTRA VOWEL SIGN VOCALIC R */
			0xA8BB,				/* SAURASHTRA VOWEL SIGN VOCALIC RR */
			0xA8BC,				/* SAURASHTRA VOWEL SIGN VOCALIC L */
			0xA8BD,				/* SAURASHTRA VOWEL SIGN VOCALIC LL */
			0xA8BE,				/* SAURASHTRA VOWEL SIGN E */
			0xA8BF,				/* SAURASHTRA VOWEL SIGN EE */
			0xA8C0,				/* SAURASHTRA VOWEL SIGN AI */
			0xA8C1,				/* SAURASHTRA VOWEL SIGN O */
			0xA8C2,				/* SAURASHTRA VOWEL SIGN OO */
			0xA8C3,				/* SAURASHTRA VOWEL SIGN AU */
			0xA952,				/* REJANG CONSONANT SIGN H */
			0xA953,				/* REJANG VIRAMA */
			0xAA2F,				/* CHAM VOWEL SIGN O */
			0xAA30,				/* CHAM VOWEL SIGN AI */
			0xAA33,				/* CHAM CONSONANT SIGN YA */
			0xAA34,				/* CHAM CONSONANT SIGN RA */
			0xAA4D				/* CHAM CONSONANT SIGN FINAL H */
		};
		const pg_wchar *StopLow = strange_letter,
				   *StopHigh = strange_letter + lengthof(strange_letter),
				   *StopMiddle;
		pg_wchar	c;

		if (prs->pgwstr)
			c = *(prs->pgwstr + prs->state->poschar);
		else
			c = (pg_wchar) *(prs->wstr + prs->state->poschar);

		while (StopLow < StopHigh)
		{
			StopMiddle = StopLow + ((StopHigh - StopLow) >> 1);
			if (*StopMiddle == c)
				return 1;
			else if (*StopMiddle < c)
				StopLow = StopMiddle + 1;
			else
				StopHigh = StopMiddle;
		}
	}

	return 0;
}