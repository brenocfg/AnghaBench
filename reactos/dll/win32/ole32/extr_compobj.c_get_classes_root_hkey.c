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
typedef  char WCHAR ;
typedef  int REGSAM ;
typedef  scalar_t__ HKEY ;
typedef  int BOOL ;

/* Variables and functions */
 scalar_t__ HKEY_CLASSES_ROOT ; 
 int KEY_WOW64_32KEY ; 
 int KEY_WOW64_64KEY ; 
 int MAXIMUM_ALLOWED ; 
 scalar_t__ classes_root_hkey ; 
 scalar_t__ create_classes_key (scalar_t__,char const*,int,scalar_t__*) ; 
 scalar_t__ create_classes_root_hkey (int) ; 

__attribute__((used)) static inline HKEY get_classes_root_hkey( HKEY hkey, REGSAM access )
{
    HKEY ret = hkey;
    const BOOL is_win64 = sizeof(void*) > sizeof(int);
    const BOOL force_wow32 = is_win64 && (access & KEY_WOW64_32KEY);

    if (hkey == HKEY_CLASSES_ROOT &&
        ((access & KEY_WOW64_64KEY) || !(ret = classes_root_hkey)))
        ret = create_classes_root_hkey(MAXIMUM_ALLOWED | (access & KEY_WOW64_64KEY));
    if (force_wow32 && ret && ret == classes_root_hkey)
    {
        static const WCHAR wow6432nodeW[] = {'W','o','w','6','4','3','2','N','o','d','e',0};
        access &= ~KEY_WOW64_32KEY;
        if (create_classes_key(classes_root_hkey, wow6432nodeW, access, &hkey))
            return 0;
        ret = hkey;
    }

    return ret;
}