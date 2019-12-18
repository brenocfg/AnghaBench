#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_10__ {scalar_t__ dwMagic; } ;
struct TYPE_8__ {scalar_t__ biCompression; scalar_t__ biPlanes; scalar_t__ biWidth; int biBitCount; int /*<<< orphan*/  biHeight; } ;
struct TYPE_9__ {TYPE_1__ bmiHeader; int /*<<< orphan*/  bmiColors; } ;
typedef  int /*<<< orphan*/  LRESULT ;
typedef  TYPE_2__* LPBITMAPINFO ;
typedef  TYPE_3__ ICCVID_Info ;

/* Variables and functions */
 scalar_t__ BI_BITFIELDS ; 
 int /*<<< orphan*/  ICCVID_CheckMask (int /*<<< orphan*/ ,int,int,int) ; 
 scalar_t__ ICCVID_MAGIC ; 
 int /*<<< orphan*/  ICCVID_dump_BITMAPINFO (TYPE_2__*) ; 
 int /*<<< orphan*/  ICERR_BADFORMAT ; 
 int /*<<< orphan*/  ICERR_BADPARAM ; 
 int /*<<< orphan*/  ICERR_OK ; 
 int /*<<< orphan*/  TRACE (char*,...) ; 

__attribute__((used)) static LRESULT ICCVID_DecompressQuery( ICCVID_Info *info, LPBITMAPINFO in, LPBITMAPINFO out )
{
    TRACE("ICM_DECOMPRESS_QUERY %p %p %p\n", info, in, out);

    if( (info==NULL) || (info->dwMagic!=ICCVID_MAGIC) )
        return ICERR_BADPARAM;

    TRACE("in: ");
    ICCVID_dump_BITMAPINFO(in);

    if( in->bmiHeader.biCompression != ICCVID_MAGIC )
        return ICERR_BADFORMAT;

    if( out )
    {
        TRACE("out: ");
        ICCVID_dump_BITMAPINFO(out);

        if( in->bmiHeader.biPlanes != out->bmiHeader.biPlanes )
            return ICERR_BADFORMAT;
        if( in->bmiHeader.biHeight != out->bmiHeader.biHeight )
        {
            if( in->bmiHeader.biHeight != -out->bmiHeader.biHeight )
                return ICERR_BADFORMAT;
            TRACE("Detected inverted height for video output\n");
        }
        if( in->bmiHeader.biWidth != out->bmiHeader.biWidth )
            return ICERR_BADFORMAT;

        switch( out->bmiHeader.biBitCount )
        {
        case 16:
            if ( out->bmiHeader.biCompression == BI_BITFIELDS )
            {
                if ( !ICCVID_CheckMask(out->bmiColors, 0x7C00, 0x03E0, 0x001F) &&
                     !ICCVID_CheckMask(out->bmiColors, 0xF800, 0x07E0, 0x001F) )
                {
                    TRACE("unsupported output bit field(s) for 16-bit colors\n");
                    return ICERR_BADFORMAT;
                }
            }
            break;
        case 24:
        case 32:
            break;
        default:
            TRACE("unsupported output bitcount = %d\n", out->bmiHeader.biBitCount );
            return ICERR_BADFORMAT;
        }
    }

    return ICERR_OK;
}