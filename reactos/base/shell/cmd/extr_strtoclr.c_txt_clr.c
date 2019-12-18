#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  WORD ;
struct TYPE_2__ {int /*<<< orphan*/  val; scalar_t__* name; } ;
typedef  int /*<<< orphan*/  LPTSTR ;
typedef  size_t INT ;

/* Variables and functions */
 int /*<<< orphan*/  _tcslen (scalar_t__*) ; 
 scalar_t__ _tcsnicmp (int /*<<< orphan*/ ,scalar_t__*,int /*<<< orphan*/ ) ; 
 TYPE_1__* clrtable ; 

__attribute__((used)) static
WORD txt_clr(LPTSTR str)
{
    INT i;

    for(i = 0; *(clrtable[i].name); i++)
        if (_tcsnicmp(str, clrtable[i].name, _tcslen(clrtable[i].name)) == 0)
            return clrtable[i].val;

    return (WORD)-1;
}