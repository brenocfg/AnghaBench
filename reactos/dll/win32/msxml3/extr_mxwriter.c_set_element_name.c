#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int /*<<< orphan*/ * element; } ;
typedef  TYPE_1__ mxwriter ;
typedef  int /*<<< orphan*/  WCHAR ;

/* Variables and functions */
 int /*<<< orphan*/ * SysAllocString (int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/ * SysAllocStringLen (int /*<<< orphan*/  const*,int) ; 
 int /*<<< orphan*/  SysFreeString (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void set_element_name(mxwriter *This, const WCHAR *name, int len)
{
    SysFreeString(This->element);
    if (name)
        This->element = len != -1 ? SysAllocStringLen(name, len) : SysAllocString(name);
    else
        This->element = NULL;
}