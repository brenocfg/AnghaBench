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
struct stifb_info {int dummy; } ;

/* Variables and functions */

__attribute__((used)) static void 
ngleGetDeviceRomData(struct stifb_info *fb)
{
#if 0
XXX: FIXME: !!!
	int	*pBytePerLongDevDepData;/* data byte == LSB */
	int 	*pRomTable;
	NgleDevRomData	*pPackedDevRomData;
	int	sizePackedDevRomData = sizeof(*pPackedDevRomData);
	char	*pCard8;
	int	i;
	char	*mapOrigin = NULL;
    
	int romTableIdx;

	pPackedDevRomData = fb->ngle_rom;

	SETUP_HW(fb);
	if (fb->id == S9000_ID_ARTIST) {
		pPackedDevRomData->cursor_pipeline_delay = 4;
		pPackedDevRomData->video_interleaves     = 4;
	} else {
		/* Get pointer to unpacked byte/long data in ROM */
		pBytePerLongDevDepData = fb->sti->regions[NGLEDEVDEPROM_CRT_REGION];

		/* Tomcat supports several resolutions: 1280x1024, 1024x768, 640x480 */
		if (fb->id == S9000_ID_TOMCAT)
	{
	    /*  jump to the correct ROM table  */
	    GET_ROMTABLE_INDEX(romTableIdx);
	    while  (romTableIdx > 0)
	    {
		pCard8 = (Card8 *) pPackedDevRomData;
		pRomTable = pBytePerLongDevDepData;
		/* Pack every fourth byte from ROM into structure */
		for (i = 0; i < sizePackedDevRomData; i++)
		{
		    *pCard8++ = (Card8) (*pRomTable++);
		}

		pBytePerLongDevDepData = (Card32 *)
			((Card8 *) pBytePerLongDevDepData +
			       pPackedDevRomData->sizeof_ngle_data);

		romTableIdx--;
	    }
	}

	pCard8 = (Card8 *) pPackedDevRomData;

	/* Pack every fourth byte from ROM into structure */
	for (i = 0; i < sizePackedDevRomData; i++)
	{
	    *pCard8++ = (Card8) (*pBytePerLongDevDepData++);
	}
    }

    SETUP_FB(fb);
#endif
}