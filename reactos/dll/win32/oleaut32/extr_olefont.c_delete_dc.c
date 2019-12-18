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

/* Variables and functions */
 int /*<<< orphan*/  DeleteDC (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  EnterCriticalSection (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  LeaveCriticalSection (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  OLEFontImpl_csHFONTLIST ; 
 int /*<<< orphan*/ * olefont_hdc ; 

__attribute__((used)) static void delete_dc(void)
{
    EnterCriticalSection(&OLEFontImpl_csHFONTLIST);
    if(olefont_hdc)
    {
        DeleteDC(olefont_hdc);
        olefont_hdc = NULL;
    }
    LeaveCriticalSection(&OLEFontImpl_csHFONTLIST);
}