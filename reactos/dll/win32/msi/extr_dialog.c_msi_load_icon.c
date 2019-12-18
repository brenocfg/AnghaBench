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
typedef  int UINT ;
typedef  int /*<<< orphan*/  MSIDATABASE ;
typedef  int /*<<< orphan*/  LPCWSTR ;
typedef  int /*<<< orphan*/  HICON ;
typedef  int DWORD ;

/* Variables and functions */
 int /*<<< orphan*/  IMAGE_ICON ; 
 int LR_DEFAULTSIZE ; 
 int LR_LOADFROMFILE ; 
 int /*<<< orphan*/  msi_load_image (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int,int) ; 
 int msidbControlAttributesFixedSize ; 
 int msidbControlAttributesIconSize16 ; 
 int msidbControlAttributesIconSize32 ; 

__attribute__((used)) static HICON msi_load_icon( MSIDATABASE *db, LPCWSTR text, UINT attributes )
{
    DWORD cx = 0, cy = 0, flags;

    flags = LR_LOADFROMFILE | LR_DEFAULTSIZE;
    if( attributes & msidbControlAttributesFixedSize )
    {
        flags &= ~LR_DEFAULTSIZE;
        if( attributes & msidbControlAttributesIconSize16 )
        {
            cx += 16;
            cy += 16;
        }
        if( attributes & msidbControlAttributesIconSize32 )
        {
            cx += 32;
            cy += 32;
        }
        /* msidbControlAttributesIconSize48 handled by above logic */
    }
    return msi_load_image( db, text, IMAGE_ICON, cx, cy, flags );
}