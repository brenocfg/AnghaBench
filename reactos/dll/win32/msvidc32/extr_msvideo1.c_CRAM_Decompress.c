#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_4__ ;
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
struct TYPE_12__ {int biBitCount; int biWidth; int biHeight; } ;
struct TYPE_11__ {TYPE_4__* lpbiOutput; void* lpOutput; int /*<<< orphan*/  lpInput; TYPE_1__* lpbiInput; } ;
struct TYPE_10__ {scalar_t__ dwMagic; int depth; } ;
struct TYPE_9__ {int biWidth; int biHeight; int biSizeImage; } ;
typedef  TYPE_2__ Msvideo1Context ;
typedef  int /*<<< orphan*/  LRESULT ;
typedef  int LONG ;
typedef  TYPE_3__ ICDECOMPRESS ;
typedef  int /*<<< orphan*/  DWORD ;

/* Variables and functions */
 scalar_t__ CRAM_MAGIC ; 
 int /*<<< orphan*/  GetProcessHeap () ; 
 void* HeapAlloc (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  HeapFree (int /*<<< orphan*/ ,int /*<<< orphan*/ ,void*) ; 
 int /*<<< orphan*/  ICERR_BADPARAM ; 
 int /*<<< orphan*/  ICERR_MEMORY ; 
 int /*<<< orphan*/  ICERR_OK ; 
 int /*<<< orphan*/  TRACE (char*,TYPE_2__*,TYPE_3__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  convert_depth (void*,int,void*,TYPE_4__*) ; 
 int get_stride (int,int) ; 
 int /*<<< orphan*/  msvideo1_decode_16bit (int,int,int /*<<< orphan*/ ,int,void*,int) ; 
 int /*<<< orphan*/  msvideo1_decode_8bit (int,int,int /*<<< orphan*/ ,int,void*,int) ; 

__attribute__((used)) static LRESULT CRAM_Decompress( Msvideo1Context *info, ICDECOMPRESS *icd, DWORD size )
{
    LONG width, height, stride, sz;
    void *output;

    TRACE("ICM_DECOMPRESS %p %p %d\n", info, icd, size);

    if( (info==NULL) || (info->dwMagic!=CRAM_MAGIC) )
        return ICERR_BADPARAM;

    /* FIXME: flags are ignored */

    width  = icd->lpbiInput->biWidth;
    height = icd->lpbiInput->biHeight;
    sz = icd->lpbiInput->biSizeImage;

    output = icd->lpOutput;

    if (icd->lpbiOutput->biBitCount != info->depth)
    {
        output = HeapAlloc(GetProcessHeap(), 0, icd->lpbiOutput->biWidth * icd->lpbiOutput->biHeight * info->depth / 8);
        if (!output) return ICERR_MEMORY;
    }

    if (info->depth == 8)
    {
        stride = get_stride(width, 8);
        msvideo1_decode_8bit( width, height, icd->lpInput, sz,
                              output, stride );
    }
    else
    {
        stride = get_stride(width, 16) / 2;
        msvideo1_decode_16bit( width, height, icd->lpInput, sz,
                               output, stride );
    }

    if (icd->lpbiOutput->biBitCount != info->depth)
    {
        convert_depth(output, info->depth, icd->lpOutput, icd->lpbiOutput);
        HeapFree(GetProcessHeap(), 0, output);
    }

    return ICERR_OK;
}