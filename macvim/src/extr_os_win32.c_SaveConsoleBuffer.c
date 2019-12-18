#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_15__   TYPE_9__ ;
typedef  struct TYPE_14__   TYPE_6__ ;
typedef  struct TYPE_13__   TYPE_4__ ;
typedef  struct TYPE_12__   TYPE_3__ ;
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ WORD ;
struct TYPE_10__ {int X; scalar_t__ Y; } ;
struct TYPE_15__ {TYPE_1__ dwSize; } ;
struct TYPE_14__ {int X; scalar_t__ Y; } ;
struct TYPE_13__ {scalar_t__ Y; scalar_t__ X; } ;
struct TYPE_12__ {int /*<<< orphan*/ * Buffer; TYPE_6__ BufferSize; TYPE_9__ Info; void* IsValid; } ;
struct TYPE_11__ {int Right; scalar_t__ Bottom; scalar_t__ Top; scalar_t__ Left; } ;
typedef  TYPE_2__ SMALL_RECT ;
typedef  int /*<<< orphan*/ * PCHAR_INFO ;
typedef  int DWORD ;
typedef  TYPE_3__ ConsoleBuffer ;
typedef  TYPE_4__ COORD ;
typedef  int /*<<< orphan*/  CHAR_INFO ;
typedef  void* BOOL ;

/* Variables and functions */
 void* FALSE ; 
 int /*<<< orphan*/  GetConsoleScreenBufferInfo (int /*<<< orphan*/ ,TYPE_9__*) ; 
 int /*<<< orphan*/  ReadConsoleOutput (int /*<<< orphan*/ ,int /*<<< orphan*/ *,TYPE_6__,TYPE_4__,TYPE_2__*) ; 
 void* TRUE ; 
 scalar_t__ alloc (int) ; 
 int /*<<< orphan*/  g_hConOut ; 
 int /*<<< orphan*/  vim_free (int /*<<< orphan*/ *) ; 

__attribute__((used)) static BOOL
SaveConsoleBuffer(
    ConsoleBuffer *cb)
{
    DWORD NumCells;
    COORD BufferCoord;
    SMALL_RECT ReadRegion;
    WORD Y, Y_incr;

    if (cb == NULL)
	return FALSE;

    if (!GetConsoleScreenBufferInfo(g_hConOut, &cb->Info))
    {
	cb->IsValid = FALSE;
	return FALSE;
    }
    cb->IsValid = TRUE;

    /*
     * Allocate a buffer large enough to hold the entire console screen
     * buffer.  If this ConsoleBuffer structure has already been initialized
     * with a buffer of the correct size, then just use that one.
     */
    if (!cb->IsValid || cb->Buffer == NULL ||
	    cb->BufferSize.X != cb->Info.dwSize.X ||
	    cb->BufferSize.Y != cb->Info.dwSize.Y)
    {
	cb->BufferSize.X = cb->Info.dwSize.X;
	cb->BufferSize.Y = cb->Info.dwSize.Y;
	NumCells = cb->BufferSize.X * cb->BufferSize.Y;
	vim_free(cb->Buffer);
	cb->Buffer = (PCHAR_INFO)alloc(NumCells * sizeof(CHAR_INFO));
	if (cb->Buffer == NULL)
	    return FALSE;
    }

    /*
     * We will now copy the console screen buffer into our buffer.
     * ReadConsoleOutput() seems to be limited as far as how much you
     * can read at a time.  Empirically, this number seems to be about
     * 12000 cells (rows * columns).  Start at position (0, 0) and copy
     * in chunks until it is all copied.  The chunks will all have the
     * same horizontal characteristics, so initialize them now.  The
     * height of each chunk will be (12000 / width).
     */
    BufferCoord.X = 0;
    ReadRegion.Left = 0;
    ReadRegion.Right = cb->Info.dwSize.X - 1;
    Y_incr = 12000 / cb->Info.dwSize.X;
    for (Y = 0; Y < cb->BufferSize.Y; Y += Y_incr)
    {
	/*
	 * Read into position (0, Y) in our buffer.
	 */
	BufferCoord.Y = Y;
	/*
	 * Read the region whose top left corner is (0, Y) and whose bottom
	 * right corner is (width - 1, Y + Y_incr - 1).  This should define
	 * a region of size width by Y_incr.  Don't worry if this region is
	 * too large for the remaining buffer; it will be cropped.
	 */
	ReadRegion.Top = Y;
	ReadRegion.Bottom = Y + Y_incr - 1;
	if (!ReadConsoleOutput(g_hConOut,	/* output handle */
		cb->Buffer,			/* our buffer */
		cb->BufferSize,			/* dimensions of our buffer */
		BufferCoord,			/* offset in our buffer */
		&ReadRegion))			/* region to save */
	{
	    vim_free(cb->Buffer);
	    cb->Buffer = NULL;
	    return FALSE;
	}
    }

    return TRUE;
}