#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int /*<<< orphan*/  WCHAR ;
typedef  int /*<<< orphan*/  HMENU ;

/* Variables and functions */
 int /*<<< orphan*/  CSIDL_COMMON_FAVORITES ; 
 int /*<<< orphan*/  CSIDL_FAVORITES ; 
 int /*<<< orphan*/  IDR_BROWSE_MAIN_MENU ; 
 int /*<<< orphan*/  LoadMenuW (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MAKEINTRESOURCEW (int /*<<< orphan*/ ) ; 
 int MAX_PATH ; 
 int /*<<< orphan*/  SHGFP_TYPE_CURRENT ; 
 scalar_t__ SHGetFolderPathW (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ S_OK ; 
 int /*<<< orphan*/  add_favs_to_menu (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  add_tbs_to_menu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  get_fav_menu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  get_tb_menu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ieframe_instance ; 

__attribute__((used)) static HMENU create_ie_menu(void)
{
    HMENU menu = LoadMenuW(ieframe_instance, MAKEINTRESOURCEW(IDR_BROWSE_MAIN_MENU));
    HMENU favmenu = get_fav_menu(menu);
    WCHAR path[MAX_PATH];

    add_tbs_to_menu(get_tb_menu(menu));

    if(SHGetFolderPathW(NULL, CSIDL_COMMON_FAVORITES, NULL, SHGFP_TYPE_CURRENT, path) == S_OK)
        add_favs_to_menu(favmenu, favmenu, path);

    if(SHGetFolderPathW(NULL, CSIDL_FAVORITES, NULL, SHGFP_TYPE_CURRENT, path) == S_OK)
        add_favs_to_menu(favmenu, favmenu, path);

    return menu;
}