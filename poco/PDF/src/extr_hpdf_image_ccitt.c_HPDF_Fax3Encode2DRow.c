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
typedef  scalar_t__ uint32 ;
struct _HPDF_CCITT_Data {int dummy; } ;
typedef  int int32 ;
typedef  int /*<<< orphan*/  HPDF_STATUS ;

/* Variables and functions */
 int /*<<< orphan*/  HPDF_OK ; 
 int PIXEL (unsigned char*,scalar_t__) ; 
 int /*<<< orphan*/  TIFFFaxBlackCodes ; 
 int /*<<< orphan*/  TIFFFaxWhiteCodes ; 
 scalar_t__ finddiff (unsigned char*,scalar_t__,scalar_t__,int) ; 
 scalar_t__ finddiff2 (unsigned char*,scalar_t__,scalar_t__,int) ; 
 int /*<<< orphan*/  horizcode ; 
 int /*<<< orphan*/  passcode ; 
 int /*<<< orphan*/  putcode (struct _HPDF_CCITT_Data*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  putspan (struct _HPDF_CCITT_Data*,scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * vcodes ; 

__attribute__((used)) static HPDF_STATUS 
HPDF_Fax3Encode2DRow(struct _HPDF_CCITT_Data *pData, unsigned char* bp, unsigned char* rp, uint32 bits)
{
#define	PIXEL(buf,ix)	((((buf)[(ix)>>3]) >> (7-((ix)&7))) & 1)
        uint32 a0 = 0;
	uint32 a1 = (PIXEL(bp, 0) != 0 ? 0 : finddiff(bp, 0, bits, 0));
	uint32 b1 = (PIXEL(rp, 0) != 0 ? 0 : finddiff(rp, 0, bits, 0));
	uint32 a2, b2;

	for (;;) {
		b2 = finddiff2(rp, b1, bits, PIXEL(rp,b1));
		if (b2 >= a1) {
			int32 d = b1 - a1;
			if (!(-3 <= d && d <= 3)) {	/* horizontal mode */
				a2 = finddiff2(bp, a1, bits, PIXEL(bp,a1));
				putcode(pData, &horizcode);
				if (a0+a1 == 0 || PIXEL(bp, a0) == 0) {
					putspan(pData, a1-a0, TIFFFaxWhiteCodes);
					putspan(pData, a2-a1, TIFFFaxBlackCodes);
				} else {
					putspan(pData, a1-a0, TIFFFaxBlackCodes);
					putspan(pData, a2-a1, TIFFFaxWhiteCodes);
				}
				a0 = a2;
			} else {			/* vertical mode */
				putcode(pData, &vcodes[d+3]);
				a0 = a1;
			}
		} else {				/* pass mode */
			putcode(pData, &passcode);
			a0 = b2;
		}
		if (a0 >= bits)
			break;
		a1 = finddiff(bp, a0, bits, PIXEL(bp,a0));
		b1 = finddiff(rp, a0, bits, !PIXEL(bp,a0));
		b1 = finddiff(rp, b1, bits, PIXEL(bp,a0));
	}
	return HPDF_OK;
#undef PIXEL
}