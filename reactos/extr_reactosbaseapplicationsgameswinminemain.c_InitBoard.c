#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {scalar_t__ IsMarkQ; scalar_t__ difficulty; int /*<<< orphan*/  hWnd; int /*<<< orphan*/  hInst; void* hLedsBMP; void* hFacesBMP; void* hMinesBMP; } ;
typedef  int /*<<< orphan*/  HMENU ;
typedef  TYPE_1__ BOARD ;

/* Variables and functions */
 int /*<<< orphan*/  CheckLevel (TYPE_1__*) ; 
 int /*<<< orphan*/  CheckMenuItem (int /*<<< orphan*/ ,unsigned int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  GetMenu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  IDI_FACES ; 
 int /*<<< orphan*/  IDI_LEDS ; 
 int /*<<< orphan*/  IDI_MINES ; 
 unsigned int IDM_BEGINNER ; 
 unsigned int IDM_MARKQ ; 
 void* LoadBitmapW (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  LoadBoard (TYPE_1__*) ; 
 int /*<<< orphan*/  MAKEINTRESOURCEW (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MF_CHECKED ; 
 int /*<<< orphan*/  MF_UNCHECKED ; 

__attribute__((used)) static void InitBoard( BOARD *p_board )
{
    HMENU hMenu;

    p_board->hMinesBMP = LoadBitmapW( p_board->hInst, MAKEINTRESOURCEW(IDI_MINES));
    p_board->hFacesBMP = LoadBitmapW( p_board->hInst, MAKEINTRESOURCEW(IDI_FACES));
    p_board->hLedsBMP = LoadBitmapW( p_board->hInst, MAKEINTRESOURCEW(IDI_LEDS));

    LoadBoard( p_board );

    hMenu = GetMenu( p_board->hWnd );
    CheckMenuItem( hMenu, IDM_BEGINNER + (unsigned) p_board->difficulty,
            MF_CHECKED );
    if( p_board->IsMarkQ )
        CheckMenuItem( hMenu, IDM_MARKQ, MF_CHECKED );
    else
        CheckMenuItem( hMenu, IDM_MARKQ, MF_UNCHECKED );
    CheckLevel( p_board );
}