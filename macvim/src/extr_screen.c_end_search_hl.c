#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int /*<<< orphan*/ * regprog; } ;
struct TYPE_4__ {TYPE_1__ rm; } ;

/* Variables and functions */
 TYPE_2__ search_hl ; 
 int /*<<< orphan*/  vim_regfree (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
end_search_hl()
{
    if (search_hl.rm.regprog != NULL)
    {
	vim_regfree(search_hl.rm.regprog);
	search_hl.rm.regprog = NULL;
    }
}