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
typedef  int /*<<< orphan*/  VOID ;
typedef  int /*<<< orphan*/  HDC ;

/* Variables and functions */
 int GDI_ERROR ; 
 int GetFontData (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  MS_MAKE_TAG (char,char,unsigned char,char) ; 
 int /*<<< orphan*/  TRACE (char*,int) ; 
 int /*<<< orphan*/ * heap_alloc (int) ; 

__attribute__((used)) static VOID *load_gsub_table(HDC hdc)
{
    VOID* GSUB_Table = NULL;
    int length = GetFontData(hdc, MS_MAKE_TAG('G', 'S', 'U', 'B'), 0, NULL, 0);
    if (length != GDI_ERROR)
    {
        GSUB_Table = heap_alloc(length);
        GetFontData(hdc, MS_MAKE_TAG('G', 'S', 'U', 'B'), 0, GSUB_Table, length);
        TRACE("Loaded GSUB table of %i bytes\n",length);
    }
    return GSUB_Table;
}