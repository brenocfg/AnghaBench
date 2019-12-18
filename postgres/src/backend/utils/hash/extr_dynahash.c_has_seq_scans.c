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
typedef  int /*<<< orphan*/  HTAB ;

/* Variables and functions */
 int num_seq_scans ; 
 int /*<<< orphan*/ ** seq_scan_tables ; 

__attribute__((used)) static bool
has_seq_scans(HTAB *hashp)
{
	int			i;

	for (i = 0; i < num_seq_scans; i++)
	{
		if (seq_scan_tables[i] == hashp)
			return true;
	}
	return false;
}