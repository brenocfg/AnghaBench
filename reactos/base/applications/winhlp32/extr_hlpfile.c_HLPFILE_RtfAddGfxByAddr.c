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
struct RtfData {int dummy; } ;
typedef  int /*<<< orphan*/  ULONG ;
typedef  int /*<<< orphan*/  HLPFILE ;
typedef  int BYTE ;
typedef  int /*<<< orphan*/  BOOL ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
 int GET_UINT (int const*,int) ; 
 unsigned int GET_USHORT (int const*,int) ; 
 int /*<<< orphan*/  HLPFILE_RtfAddBitmap (struct RtfData*,int /*<<< orphan*/ *,int const*,int,int) ; 
 int /*<<< orphan*/  HLPFILE_RtfAddMetaFile (struct RtfData*,int /*<<< orphan*/ *,int const*,int) ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  WINE_FIXME (char*,...) ; 
 int /*<<< orphan*/  WINE_TRACE (char*,unsigned int,int) ; 

__attribute__((used)) static  BOOL    HLPFILE_RtfAddGfxByAddr(struct RtfData* rd, HLPFILE *hlpfile,
                                        const BYTE* ref, ULONG size)
{
    unsigned    i, numpict;

    numpict = GET_USHORT(ref, 2);
    WINE_TRACE("Got picture magic=%04x #=%d\n", GET_USHORT(ref, 0), numpict);

    for (i = 0; i < numpict; i++)
    {
        const BYTE*     beg;
        const BYTE*     ptr;
        BYTE            type, pack;

        WINE_TRACE("Offset[%d] = %x\n", i, GET_UINT(ref, (1 + i) * 4));
        beg = ptr = ref + GET_UINT(ref, (1 + i) * 4);

        type = *ptr++;
        pack = *ptr++;

        switch (type)
        {
        case 5: /* device dependent bmp */
        case 6: /* device independent bmp */
            HLPFILE_RtfAddBitmap(rd, hlpfile, beg, type, pack);
            break;
        case 8:
            HLPFILE_RtfAddMetaFile(rd, hlpfile, beg, pack);
            break;
        default: WINE_FIXME("Unknown type %u\n", type); return FALSE;
        }

        /* FIXME: hotspots */

        /* FIXME: implement support for multiple picture format */
        if (numpict != 1) WINE_FIXME("Supporting only one bitmap format per logical bitmap (for now). Using first format\n");
        break;
    }
    return TRUE;
}