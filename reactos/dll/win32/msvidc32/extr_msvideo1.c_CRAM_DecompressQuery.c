#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {int biBitCount; int /*<<< orphan*/  biWidth; int /*<<< orphan*/  biHeight; int /*<<< orphan*/  biPlanes; int /*<<< orphan*/  biCompression; } ;
struct TYPE_9__ {TYPE_1__ bmiHeader; } ;
struct TYPE_8__ {int /*<<< orphan*/  dwMagic; } ;
typedef  TYPE_2__ Msvideo1Context ;
typedef  int /*<<< orphan*/  LRESULT ;
typedef  TYPE_3__* LPBITMAPINFO ;

/* Variables and functions */
 int /*<<< orphan*/  CRAM_MAGIC ; 
 int /*<<< orphan*/  ICERR_BADFORMAT ; 
 int /*<<< orphan*/  ICERR_BADPARAM ; 
 int /*<<< orphan*/  ICERR_OK ; 
 int /*<<< orphan*/  MSVC_MAGIC ; 
 int /*<<< orphan*/  TRACE (char*,...) ; 
 int /*<<< orphan*/  WHAM_MAGIC ; 

__attribute__((used)) static LRESULT
CRAM_DecompressQuery( Msvideo1Context *info, LPBITMAPINFO in, LPBITMAPINFO out )
{
    TRACE("ICM_DECOMPRESS_QUERY %p %p %p\n", info, in, out);

    if( (info==NULL) || (info->dwMagic!=CRAM_MAGIC) )
        return ICERR_BADPARAM;

    TRACE("in->planes  = %d\n", in->bmiHeader.biPlanes );
    TRACE("in->bpp     = %d\n", in->bmiHeader.biBitCount );
    TRACE("in->height  = %d\n", in->bmiHeader.biHeight );
    TRACE("in->width   = %d\n", in->bmiHeader.biWidth );
    TRACE("in->compr   = 0x%x\n", in->bmiHeader.biCompression );

    if( ( in->bmiHeader.biCompression != CRAM_MAGIC ) &&
        ( in->bmiHeader.biCompression != MSVC_MAGIC ) &&
        ( in->bmiHeader.biCompression != WHAM_MAGIC ) )
    {
        TRACE("can't do 0x%x compression\n", in->bmiHeader.biCompression);
        return ICERR_BADFORMAT;
    }

    if( ( in->bmiHeader.biBitCount != 16 ) &&
        ( in->bmiHeader.biBitCount != 8 ) )
    {
        TRACE("can't do %d bpp\n", in->bmiHeader.biBitCount );
        return ICERR_BADFORMAT;
    }

    /* output must be same dimensions as input */
    if( out )
    {
        TRACE("out->planes = %d\n", out->bmiHeader.biPlanes );
        TRACE("out->bpp    = %d\n", out->bmiHeader.biBitCount );
        TRACE("out->height = %d\n", out->bmiHeader.biHeight );
        TRACE("out->width  = %d\n", out->bmiHeader.biWidth );

        if ((in->bmiHeader.biBitCount != out->bmiHeader.biBitCount) &&
            (in->bmiHeader.biBitCount != 16 || out->bmiHeader.biBitCount != 24))
        {
            TRACE("incompatible depth requested\n");
            return ICERR_BADFORMAT;
        }

        if(( in->bmiHeader.biPlanes != out->bmiHeader.biPlanes ) ||
          ( in->bmiHeader.biHeight != out->bmiHeader.biHeight ) ||
          ( in->bmiHeader.biWidth != out->bmiHeader.biWidth ))
        {
            TRACE("incompatible output requested\n");
            return ICERR_BADFORMAT;
        }
    }

    TRACE("OK!\n");
    return ICERR_OK;
}