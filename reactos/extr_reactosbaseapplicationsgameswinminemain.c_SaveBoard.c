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
struct TYPE_4__ {int /*<<< orphan*/  y; int /*<<< orphan*/  x; } ;
struct TYPE_5__ {int /*<<< orphan*/ * best_time; int /*<<< orphan*/ * best_name; int /*<<< orphan*/  IsMarkQ; int /*<<< orphan*/  mines; int /*<<< orphan*/  cols; int /*<<< orphan*/  rows; int /*<<< orphan*/  difficulty; TYPE_1__ pos; } ;
typedef  int /*<<< orphan*/  LPBYTE ;
typedef  int /*<<< orphan*/  HKEY ;
typedef  TYPE_2__ BOARD ;

/* Variables and functions */
 scalar_t__ ERROR_SUCCESS ; 
 int /*<<< orphan*/  HKEY_CURRENT_USER ; 
 int /*<<< orphan*/  KEY_WRITE ; 
 int /*<<< orphan*/  MAX_PLAYER_NAME_SIZE ; 
 int /*<<< orphan*/  REG_DWORD ; 
 int /*<<< orphan*/  REG_OPTION_NON_VOLATILE ; 
 int /*<<< orphan*/  REG_SZ ; 
 int /*<<< orphan*/  RegCloseKey (int /*<<< orphan*/ ) ; 
 scalar_t__ RegCreateKeyExW (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  RegSetValueExW (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/ * difficultyW ; 
 int /*<<< orphan*/ * heightW ; 
 int /*<<< orphan*/  lstrcpynW (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 int lstrlenW (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * markW ; 
 int /*<<< orphan*/ * minesW ; 
 int /*<<< orphan*/  nameW ; 
 int /*<<< orphan*/  registry_key ; 
 int /*<<< orphan*/  timeW ; 
 int /*<<< orphan*/ * widthW ; 
 int /*<<< orphan*/  wsprintfW (int /*<<< orphan*/ *,int /*<<< orphan*/ ,unsigned int) ; 
 int /*<<< orphan*/ * xposW ; 
 int /*<<< orphan*/ * yposW ; 

__attribute__((used)) static void SaveBoard( BOARD *p_board )
{
    HKEY hkey;
    unsigned i;
    WCHAR data[MAX_PLAYER_NAME_SIZE+1];
    WCHAR key_name[8];

    if( RegCreateKeyExW( HKEY_CURRENT_USER, registry_key,
	        0, NULL,
                REG_OPTION_NON_VOLATILE, KEY_WRITE, NULL,
                &hkey, NULL ) != ERROR_SUCCESS)
        return;

    RegSetValueExW( hkey, xposW, 0, REG_DWORD, (LPBYTE) &p_board->pos.x, sizeof(p_board->pos.x) );
    RegSetValueExW( hkey, yposW, 0, REG_DWORD, (LPBYTE) &p_board->pos.y, sizeof(p_board->pos.y) );
    RegSetValueExW( hkey, difficultyW, 0, REG_DWORD, (LPBYTE) &p_board->difficulty, sizeof(p_board->difficulty) );
    RegSetValueExW( hkey, heightW, 0, REG_DWORD, (LPBYTE) &p_board->rows, sizeof(p_board->rows) );
    RegSetValueExW( hkey, widthW, 0, REG_DWORD, (LPBYTE) &p_board->cols, sizeof(p_board->cols) );
    RegSetValueExW( hkey, minesW, 0, REG_DWORD, (LPBYTE) &p_board->mines, sizeof(p_board->mines) );
    RegSetValueExW( hkey, markW, 0, REG_DWORD, (LPBYTE) &p_board->IsMarkQ, sizeof(p_board->IsMarkQ) );

    for( i = 0; i < 3; i++ ) {
        wsprintfW( key_name, nameW, i+1 );
        lstrcpynW( data, p_board->best_name[i], sizeof(data)/sizeof(WCHAR) );
        RegSetValueExW( hkey, key_name, 0, REG_SZ, (LPBYTE) data, (lstrlenW(data)+1) * sizeof(WCHAR) );
    }

    for( i = 0; i < 3; i++ ) {
        wsprintfW( key_name, timeW, i+1 );
        RegSetValueExW( hkey, key_name, 0, REG_DWORD, (LPBYTE) &p_board->best_time[i], sizeof(p_board->best_time[i]) );
    }
    RegCloseKey( hkey );
}