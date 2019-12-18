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
typedef  int /*<<< orphan*/  ret ;
typedef  int /*<<< orphan*/  WCHAR ;
typedef  scalar_t__ UINT ;
typedef  int /*<<< orphan*/  LCID ;

/* Variables and functions */
 int /*<<< orphan*/  GetLocaleInfoW (int /*<<< orphan*/ ,int,int /*<<< orphan*/ *,int) ; 
 int LOCALE_IDEFAULTANSICODEPAGE ; 
 int LOCALE_RETURN_NUMBER ; 

__attribute__((used)) static inline UINT get_lcid_codepage( LCID lcid )
{
    UINT ret;
    if (!GetLocaleInfoW( lcid, LOCALE_IDEFAULTANSICODEPAGE|LOCALE_RETURN_NUMBER, (WCHAR *)&ret,
                         sizeof(ret)/sizeof(WCHAR) )) ret = 0;
    return ret;
}