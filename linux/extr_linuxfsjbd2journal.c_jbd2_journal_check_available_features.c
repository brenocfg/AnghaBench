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
struct TYPE_3__ {int j_format_version; } ;
typedef  TYPE_1__ journal_t ;

/* Variables and functions */
 unsigned long JBD2_KNOWN_COMPAT_FEATURES ; 
 unsigned long JBD2_KNOWN_INCOMPAT_FEATURES ; 
 unsigned long JBD2_KNOWN_ROCOMPAT_FEATURES ; 

int jbd2_journal_check_available_features (journal_t *journal, unsigned long compat,
				      unsigned long ro, unsigned long incompat)
{
	if (!compat && !ro && !incompat)
		return 1;

	/* We can support any known requested features iff the
	 * superblock is in version 2.  Otherwise we fail to support any
	 * extended sb features. */

	if (journal->j_format_version != 2)
		return 0;

	if ((compat   & JBD2_KNOWN_COMPAT_FEATURES) == compat &&
	    (ro       & JBD2_KNOWN_ROCOMPAT_FEATURES) == ro &&
	    (incompat & JBD2_KNOWN_INCOMPAT_FEATURES) == incompat)
		return 1;

	return 0;
}