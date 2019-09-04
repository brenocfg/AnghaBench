#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {struct TYPE_4__* sb_prev; } ;
typedef  TYPE_1__ msgchunk_T ;

/* Variables and functions */
 TYPE_1__* last_msgchunk ; 
 int /*<<< orphan*/  vim_free (TYPE_1__*) ; 

void
clear_sb_text()
{
    msgchunk_T	*mp;

    while (last_msgchunk != NULL)
    {
	mp = last_msgchunk->sb_prev;
	vim_free(last_msgchunk);
	last_msgchunk = mp;
    }
}