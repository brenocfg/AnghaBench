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
struct TYPE_2__ {scalar_t__ status; int /*<<< orphan*/  busid_lock; int /*<<< orphan*/  name; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUSID_SIZE ; 
 scalar_t__ STUB_BUSID_ADDED ; 
 scalar_t__ STUB_BUSID_OTHER ; 
 scalar_t__ STUB_BUSID_REMOV ; 
 TYPE_1__* busid_table ; 
 int /*<<< orphan*/  busid_table_lock ; 
 int get_busid_idx (char*) ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 

int del_match_busid(char *busid)
{
	int idx;
	int ret = -1;

	spin_lock(&busid_table_lock);
	idx = get_busid_idx(busid);
	if (idx < 0)
		goto out;

	/* found */
	ret = 0;

	spin_lock(&busid_table[idx].busid_lock);

	if (busid_table[idx].status == STUB_BUSID_OTHER)
		memset(busid_table[idx].name, 0, BUSID_SIZE);

	if ((busid_table[idx].status != STUB_BUSID_OTHER) &&
	    (busid_table[idx].status != STUB_BUSID_ADDED))
		busid_table[idx].status = STUB_BUSID_REMOV;

	spin_unlock(&busid_table[idx].busid_lock);
out:
	spin_unlock(&busid_table_lock);

	return ret;
}