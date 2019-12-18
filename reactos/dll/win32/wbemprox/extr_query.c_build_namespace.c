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
struct view {scalar_t__ proplist; } ;
typedef  char WCHAR ;
typedef  int /*<<< orphan*/ * BSTR ;

/* Variables and functions */
 int /*<<< orphan*/ * SysAllocString (char const*) ; 

__attribute__((used)) static BSTR build_namespace( const struct view *view )
{
    static const WCHAR cimv2W[] = {'R','O','O','T','\\','C','I','M','V','2',0};

    if (view->proplist) return NULL;
    return SysAllocString( cimv2W );
}