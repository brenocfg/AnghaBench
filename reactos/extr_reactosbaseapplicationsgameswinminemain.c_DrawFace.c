#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int /*<<< orphan*/  top; int /*<<< orphan*/  left; } ;
struct TYPE_5__ {int face_bmp; TYPE_1__ face_rect; int /*<<< orphan*/  hFacesBMP; } ;
typedef  int /*<<< orphan*/  HGDIOBJ ;
typedef  int /*<<< orphan*/  HDC ;
typedef  TYPE_2__ BOARD ;

/* Variables and functions */
 int /*<<< orphan*/  BitBlt (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int FACE_HEIGHT ; 
 int /*<<< orphan*/  FACE_WIDTH ; 
 int /*<<< orphan*/  SRCCOPY ; 
 int /*<<< orphan*/  SelectObject (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void DrawFace( HDC hdc, HDC hMemDC, BOARD *p_board )
{
    HGDIOBJ hOldObj;

    hOldObj = SelectObject (hMemDC, p_board->hFacesBMP);

    BitBlt( hdc,
        p_board->face_rect.left,
        p_board->face_rect.top,
        FACE_WIDTH,
        FACE_HEIGHT,
        hMemDC, 0, p_board->face_bmp * FACE_HEIGHT, SRCCOPY);

    SelectObject( hMemDC, hOldObj );
}