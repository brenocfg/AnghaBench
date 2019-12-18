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
typedef  int LCTYPE ;
typedef  int /*<<< orphan*/  BOOL ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
#define  LOCALE_SMONTHNAME1 140 
#define  LOCALE_SMONTHNAME10 139 
#define  LOCALE_SMONTHNAME11 138 
#define  LOCALE_SMONTHNAME12 137 
#define  LOCALE_SMONTHNAME13 136 
#define  LOCALE_SMONTHNAME2 135 
#define  LOCALE_SMONTHNAME3 134 
#define  LOCALE_SMONTHNAME4 133 
#define  LOCALE_SMONTHNAME5 132 
#define  LOCALE_SMONTHNAME6 131 
#define  LOCALE_SMONTHNAME7 130 
#define  LOCALE_SMONTHNAME8 129 
#define  LOCALE_SMONTHNAME9 128 
 int /*<<< orphan*/  TRUE ; 

__attribute__((used)) static BOOL is_genitive_name_supported( LCTYPE lctype )
{
    switch(lctype & 0xffff)
    {
    case LOCALE_SMONTHNAME1:
    case LOCALE_SMONTHNAME2:
    case LOCALE_SMONTHNAME3:
    case LOCALE_SMONTHNAME4:
    case LOCALE_SMONTHNAME5:
    case LOCALE_SMONTHNAME6:
    case LOCALE_SMONTHNAME7:
    case LOCALE_SMONTHNAME8:
    case LOCALE_SMONTHNAME9:
    case LOCALE_SMONTHNAME10:
    case LOCALE_SMONTHNAME11:
    case LOCALE_SMONTHNAME12:
    case LOCALE_SMONTHNAME13:
         return TRUE;
    default:
         return FALSE;
    }
}