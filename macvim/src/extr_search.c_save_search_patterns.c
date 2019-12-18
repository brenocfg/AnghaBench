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
struct TYPE_3__ {int /*<<< orphan*/ * pat; } ;

/* Variables and functions */
 int /*<<< orphan*/  last_idx ; 
 int /*<<< orphan*/  no_hlsearch ; 
 int /*<<< orphan*/  save_level ; 
 int /*<<< orphan*/  saved_last_idx ; 
 int /*<<< orphan*/  saved_no_hlsearch ; 
 TYPE_1__* saved_spats ; 
 TYPE_1__* spats ; 
 void* vim_strsave (int /*<<< orphan*/ *) ; 

void
save_search_patterns()
{
    if (save_level++ == 0)
    {
	saved_spats[0] = spats[0];
	if (spats[0].pat != NULL)
	    saved_spats[0].pat = vim_strsave(spats[0].pat);
	saved_spats[1] = spats[1];
	if (spats[1].pat != NULL)
	    saved_spats[1].pat = vim_strsave(spats[1].pat);
	saved_last_idx = last_idx;
# ifdef FEAT_SEARCH_EXTRA
	saved_no_hlsearch = no_hlsearch;
# endif
    }
}