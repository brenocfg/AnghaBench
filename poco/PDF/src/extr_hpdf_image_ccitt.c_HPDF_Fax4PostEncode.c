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
struct _HPDF_CCITT_Data {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  EOL ; 
 int /*<<< orphan*/  HPDF_CCITT_FlushData (struct _HPDF_CCITT_Data*) ; 
 int /*<<< orphan*/  HPDF_Fax3PutBits (struct _HPDF_CCITT_Data*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void
HPDF_Fax4PostEncode(struct _HPDF_CCITT_Data *pData)
{
	/* HPDF_Fax3CodecState *sp = EncoderState(pData); */

	/* terminate strip w/ EOFB */
	HPDF_Fax3PutBits(pData, EOL, 12);
	HPDF_Fax3PutBits(pData, EOL, 12);
	/*if (sp->bit != 8)
		HPDF_Fax3FlushBits(pData, sp);	
		*/
	HPDF_CCITT_FlushData(pData);
}