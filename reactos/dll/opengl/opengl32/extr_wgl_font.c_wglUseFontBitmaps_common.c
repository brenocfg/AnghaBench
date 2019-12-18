#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_21__   TYPE_8__ ;
typedef  struct TYPE_20__   TYPE_7__ ;
typedef  struct TYPE_19__   TYPE_6__ ;
typedef  struct TYPE_18__   TYPE_5__ ;
typedef  struct TYPE_17__   TYPE_4__ ;
typedef  struct TYPE_16__   TYPE_3__ ;
typedef  struct TYPE_15__   TYPE_2__ ;
typedef  struct TYPE_14__   TYPE_1__ ;

/* Type definitions */
typedef  int UINT_PTR ;
struct TYPE_21__ {int /*<<< orphan*/  (* PixelStorei ) (int /*<<< orphan*/ ,int) ;int /*<<< orphan*/  (* EndList ) () ;int /*<<< orphan*/  (* Bitmap ) (int,unsigned int,scalar_t__,scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ,void*) ;int /*<<< orphan*/  (* NewList ) (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ;int /*<<< orphan*/  (* GetIntegerv ) (int /*<<< orphan*/ ,int*) ;} ;
struct TYPE_18__ {scalar_t__ y; int /*<<< orphan*/  x; } ;
struct TYPE_20__ {unsigned int gmBlackBoxX; unsigned int gmBlackBoxY; int /*<<< orphan*/  gmCellIncY; int /*<<< orphan*/  gmCellIncX; TYPE_5__ gmptGlyphOrigin; } ;
struct TYPE_17__ {int member_1; int /*<<< orphan*/  member_0; } ;
struct TYPE_16__ {int /*<<< orphan*/  member_1; int /*<<< orphan*/  member_0; } ;
struct TYPE_15__ {int /*<<< orphan*/  member_1; int /*<<< orphan*/  member_0; } ;
struct TYPE_14__ {int member_1; int /*<<< orphan*/  member_0; } ;
struct TYPE_19__ {TYPE_4__ member_3; TYPE_3__ member_2; TYPE_2__ member_1; TYPE_1__ member_0; } ;
typedef  TYPE_6__ MAT2 ;
typedef  int /*<<< orphan*/  HDC ;
typedef  TYPE_7__ GLYPHMETRICS ;
typedef  TYPE_8__ GLDISPATCHTABLE ;
typedef  unsigned int DWORD ;
typedef  int BOOL ;

/* Variables and functions */
 int FALSE ; 
 unsigned int GDI_ERROR ; 
 int /*<<< orphan*/  GGO_BITMAP ; 
 int /*<<< orphan*/  GL_COMPILE ; 
 int /*<<< orphan*/  GL_UNPACK_ALIGNMENT ; 
 unsigned int GetGlyphOutlineA (int /*<<< orphan*/ ,unsigned int,int /*<<< orphan*/ ,TYPE_7__*,unsigned int,void*,TYPE_6__ const*) ; 
 unsigned int GetGlyphOutlineW (int /*<<< orphan*/ ,unsigned int,int /*<<< orphan*/ ,TYPE_7__*,unsigned int,void*,TYPE_6__ const*) ; 
 int /*<<< orphan*/  GetProcessHeap () ; 
 int /*<<< orphan*/  HEAP_ZERO_MEMORY ; 
 void* HeapAlloc (int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned int) ; 
 int /*<<< orphan*/  HeapFree (int /*<<< orphan*/ ,int /*<<< orphan*/ ,void*) ; 
 TYPE_8__* IntGetCurrentDispatchTable () ; 
 int /*<<< orphan*/  TRACE (char*,...) ; 
 scalar_t__ TRACE_ON (int /*<<< orphan*/ ) ; 
 int TRUE ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ,int*) ; 
 int /*<<< orphan*/  stub2 (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  stub3 (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub4 (int,unsigned int,scalar_t__,scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ,void*) ; 
 int /*<<< orphan*/  stub5 (int,unsigned int,scalar_t__,scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ,void*) ; 
 int /*<<< orphan*/  stub6 () ; 
 int /*<<< orphan*/  stub7 (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  wgl ; 

__attribute__((used)) static BOOL wglUseFontBitmaps_common( HDC hdc, DWORD first, DWORD count, DWORD listBase, BOOL unicode )
{
    const GLDISPATCHTABLE * funcs = IntGetCurrentDispatchTable();
    GLYPHMETRICS gm;
    unsigned int glyph, size = 0;
    void *bitmap = NULL, *gl_bitmap = NULL;
    int org_alignment;
    BOOL ret = TRUE;

    funcs->GetIntegerv(GL_UNPACK_ALIGNMENT, &org_alignment);
    funcs->PixelStorei(GL_UNPACK_ALIGNMENT, 4);

    for (glyph = first; glyph < first + count; glyph++) {
        static const MAT2 identity = { {0,1},{0,0},{0,0},{0,1} };
        unsigned int needed_size, height, width, width_int;

        if (unicode)
            needed_size = GetGlyphOutlineW(hdc, glyph, GGO_BITMAP, &gm, 0, NULL, &identity);
        else
            needed_size = GetGlyphOutlineA(hdc, glyph, GGO_BITMAP, &gm, 0, NULL, &identity);

        TRACE("Glyph: %3d / List: %d size %d\n", glyph, listBase, needed_size);
        if (needed_size == GDI_ERROR) {
            ret = FALSE;
            break;
        }

        if (needed_size > size) {
            size = needed_size;
            HeapFree(GetProcessHeap(), 0, bitmap);
            HeapFree(GetProcessHeap(), 0, gl_bitmap);
            bitmap = HeapAlloc(GetProcessHeap(), HEAP_ZERO_MEMORY, size);
            gl_bitmap = HeapAlloc(GetProcessHeap(), HEAP_ZERO_MEMORY, size);
        }
        if (unicode)
            ret = (GetGlyphOutlineW(hdc, glyph, GGO_BITMAP, &gm, size, bitmap, &identity) != GDI_ERROR);
        else
            ret = (GetGlyphOutlineA(hdc, glyph, GGO_BITMAP, &gm, size, bitmap, &identity) != GDI_ERROR);
        if (!ret) break;

        if (TRACE_ON(wgl)) {
            unsigned int bitmask;
            unsigned char *bitmap_ = bitmap;

            TRACE("  - bbox: %d x %d\n", gm.gmBlackBoxX, gm.gmBlackBoxY);
            TRACE("  - origin: (%d, %d)\n", gm.gmptGlyphOrigin.x, gm.gmptGlyphOrigin.y);
            TRACE("  - increment: %d - %d\n", gm.gmCellIncX, gm.gmCellIncY);
            if (needed_size != 0) {
                TRACE("  - bitmap:\n");
                for (height = 0; height < gm.gmBlackBoxY; height++) {
                    TRACE("      ");
                    for (width = 0, bitmask = 0x80; width < gm.gmBlackBoxX; width++, bitmask >>= 1) {
                        if (bitmask == 0) {
                            bitmap_ += 1;
                            bitmask = 0x80;
                        }
                        if (*bitmap_ & bitmask)
                            TRACE("*");
                        else
                            TRACE(" ");
                    }
                    bitmap_ += (4 - ((UINT_PTR)bitmap_ & 0x03));
                    TRACE("\n");
                }
            }
        }

         /* In OpenGL, the bitmap is drawn from the bottom to the top... So we need to invert the
         * glyph for it to be drawn properly.
         */
        if (needed_size != 0) {
            width_int = (gm.gmBlackBoxX + 31) / 32;
            for (height = 0; height < gm.gmBlackBoxY; height++) {
                for (width = 0; width < width_int; width++) {
                    ((int *) gl_bitmap)[(gm.gmBlackBoxY - height - 1) * width_int + width] =
                    ((int *) bitmap)[height * width_int + width];
                }
            }
        }

        funcs->NewList(listBase++, GL_COMPILE);
        if (needed_size != 0) {
            funcs->Bitmap(gm.gmBlackBoxX, gm.gmBlackBoxY,
                    0 - gm.gmptGlyphOrigin.x, (int) gm.gmBlackBoxY - gm.gmptGlyphOrigin.y,
                    gm.gmCellIncX, gm.gmCellIncY,
                    gl_bitmap);
        } else {
            /* This is the case of 'empty' glyphs like the space character */
            funcs->Bitmap(0, 0, 0, 0, gm.gmCellIncX, gm.gmCellIncY, NULL);
        }
        funcs->EndList();
    }

    funcs->PixelStorei(GL_UNPACK_ALIGNMENT, org_alignment);
    HeapFree(GetProcessHeap(), 0, bitmap);
    HeapFree(GetProcessHeap(), 0, gl_bitmap);
    return ret;
}