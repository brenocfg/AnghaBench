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
typedef  int /*<<< orphan*/  data ;
typedef  int /*<<< orphan*/  WCHAR ;
struct TYPE_4__ {scalar_t__ y; scalar_t__ x; } ;
struct TYPE_5__ {int* best_time; int /*<<< orphan*/ * best_name; int /*<<< orphan*/  hInst; int /*<<< orphan*/  IsMarkQ; int /*<<< orphan*/  difficulty; int /*<<< orphan*/  mines; int /*<<< orphan*/  cols; int /*<<< orphan*/  rows; TYPE_1__ pos; } ;
typedef  int /*<<< orphan*/ * LPBYTE ;
typedef  int /*<<< orphan*/  HKEY ;
typedef  int DWORD ;
typedef  int /*<<< orphan*/  BYTE ;
typedef  TYPE_2__ BOARD ;

/* Variables and functions */
 int /*<<< orphan*/  BEGINNER ; 
 int /*<<< orphan*/  BEGINNER_COLS ; 
 int /*<<< orphan*/  BEGINNER_MINES ; 
 int /*<<< orphan*/  BEGINNER_ROWS ; 
 scalar_t__ ERROR_SUCCESS ; 
 int /*<<< orphan*/  HKEY_CURRENT_USER ; 
 int /*<<< orphan*/  IDS_NOBODY ; 
 int /*<<< orphan*/  KEY_QUERY_VALUE ; 
 int /*<<< orphan*/  LoadStringW (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int MAX_PLAYER_NAME_SIZE ; 
 int /*<<< orphan*/  RegCloseKey (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  RegOpenKeyExW (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ RegQueryValueExW (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int*,int /*<<< orphan*/ *,int*) ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/ * difficultyW ; 
 int /*<<< orphan*/ * heightW ; 
 int /*<<< orphan*/  lstrcpynW (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/ * markW ; 
 int /*<<< orphan*/ * minesW ; 
 int /*<<< orphan*/  nameW ; 
 int /*<<< orphan*/  registry_key ; 
 int /*<<< orphan*/  timeW ; 
 int /*<<< orphan*/ * widthW ; 
 int /*<<< orphan*/  wsprintfW (int /*<<< orphan*/ *,int /*<<< orphan*/ ,unsigned int) ; 
 int /*<<< orphan*/ * xposW ; 
 int /*<<< orphan*/ * yposW ; 

__attribute__((used)) static void LoadBoard( BOARD *p_board )
{
    DWORD size;
    DWORD type;
    HKEY hkey;
    WCHAR data[MAX_PLAYER_NAME_SIZE+1];
    WCHAR key_name[8];
    unsigned i;

    RegOpenKeyExW( HKEY_CURRENT_USER, registry_key, 0, KEY_QUERY_VALUE, &hkey );

    size = sizeof( p_board->pos.x );
    if( RegQueryValueExW( hkey, xposW, NULL, &type, (BYTE*) &p_board->pos.x, &size ) )
	p_board->pos.x = 0;

    size = sizeof( p_board->pos.y );
    if( RegQueryValueExW( hkey, yposW, NULL, &type, (BYTE*) &p_board->pos.y, &size ) )
        p_board->pos.y = 0;

    size = sizeof( p_board->rows );
    if( RegQueryValueExW( hkey, heightW, NULL, &type, (BYTE*) &p_board->rows, &size ) )
        p_board->rows = BEGINNER_ROWS;

    size = sizeof( p_board->cols );
    if( RegQueryValueExW( hkey, widthW, NULL, &type, (BYTE*) &p_board->cols, &size ) )
        p_board->cols = BEGINNER_COLS;

    size = sizeof( p_board->mines );
    if( RegQueryValueExW( hkey, minesW, NULL, &type, (BYTE*) &p_board->mines, &size ) )
        p_board->mines = BEGINNER_MINES;

    size = sizeof( p_board->difficulty );
    if( RegQueryValueExW( hkey, difficultyW, NULL, &type, (BYTE*) &p_board->difficulty, &size ) )
        p_board->difficulty = BEGINNER;

    size = sizeof( p_board->IsMarkQ );
    if( RegQueryValueExW( hkey, markW, NULL, &type, (BYTE*) &p_board->IsMarkQ, &size ) )
        p_board->IsMarkQ = TRUE;

    for( i = 0; i < 3; i++ ) {
        wsprintfW( key_name, nameW, i+1 );
        size = sizeof( data );
        if( RegQueryValueExW( hkey, key_name, NULL, &type,
                (LPBYTE) data, &size ) == ERROR_SUCCESS )
            lstrcpynW( p_board->best_name[i], data, sizeof(p_board->best_name[i])/sizeof(WCHAR) );
        else
            LoadStringW( p_board->hInst, IDS_NOBODY, p_board->best_name[i], MAX_PLAYER_NAME_SIZE+1 );
    }

    for( i = 0; i < 3; i++ ) {
        wsprintfW( key_name, timeW, i+1 );
        size = sizeof( p_board->best_time[i] );
        if( RegQueryValueExW( hkey, key_name, NULL, &type, (BYTE*) &p_board->best_time[i], &size ) )
            p_board->best_time[i] = 999;
    }
    RegCloseKey( hkey );
}