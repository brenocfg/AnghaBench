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
struct TYPE_7__ {int biBitCount; } ;
struct TYPE_9__ {TYPE_1__ bmiHeader; } ;
struct TYPE_8__ {scalar_t__ dwMagic; int depth; } ;
typedef  TYPE_2__ Msvideo1Context ;
typedef  int /*<<< orphan*/  LRESULT ;
typedef  TYPE_3__* LPBITMAPINFO ;

/* Variables and functions */
 scalar_t__ CRAM_MAGIC ; 
 int /*<<< orphan*/  FIXME (char*,int) ; 
 int /*<<< orphan*/  ICERR_BADPARAM ; 
 int /*<<< orphan*/  ICERR_OK ; 
 int /*<<< orphan*/  TRACE (char*,...) ; 

__attribute__((used)) static LRESULT CRAM_DecompressBegin( Msvideo1Context *info, LPBITMAPINFO in, LPBITMAPINFO out )
{
    TRACE("ICM_DECOMPRESS_BEGIN %p %p %p\n", info, in, out);

    if( (info==NULL) || (info->dwMagic!=CRAM_MAGIC) )
        return ICERR_BADPARAM;

    TRACE("bitmap is %d bpp\n", in->bmiHeader.biBitCount);
    if( in->bmiHeader.biBitCount == 8 )
        info->depth = 8;
    else if( in->bmiHeader.biBitCount == 16 )
        info->depth = 16;
    else
    {
        info->depth = 0;
        FIXME("Unsupported output format %i\n", in->bmiHeader.biBitCount);
    }

    return ICERR_OK;
}