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
typedef  int /*<<< orphan*/  bstr ;

/* Variables and functions */
 int /*<<< orphan*/  bstr0 (char*) ; 
 int /*<<< orphan*/  bstr_xappend (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void add_indent(bstr *b, int indent)
{
    if (indent < 0)
        return;
    bstr_xappend(NULL, b, bstr0("\n"));
    for (int n = 0; n < indent; n++)
        bstr_xappend(NULL, b, bstr0(" "));
}