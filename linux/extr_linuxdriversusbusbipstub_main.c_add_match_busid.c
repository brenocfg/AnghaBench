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
struct TYPE_2__ {scalar_t__ status; int /*<<< orphan*/  busid_lock; int /*<<< orphan*/ * name; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUSID_SIZE ; 
 int MAX_BUSID ; 
 scalar_t__ STUB_BUSID_ADDED ; 
 scalar_t__ STUB_BUSID_ALLOC ; 
 scalar_t__ STUB_BUSID_REMOV ; 
 TYPE_1__* busid_table ; 
 int /*<<< orphan*/  busid_table_lock ; 
 scalar_t__ get_busid_idx (char*) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  strlcpy (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int add_match_busid(char *busid)
{
	int i;
	int ret = -1;

	spin_lock(&busid_table_lock);
	/* already registered? */
	if (get_busid_idx(busid) >= 0) {
		ret = 0;
		goto out;
	}

	for (i = 0; i < MAX_BUSID; i++) {
		spin_lock(&busid_table[i].busid_lock);
		if (!busid_table[i].name[0]) {
			strlcpy(busid_table[i].name, busid, BUSID_SIZE);
			if ((busid_table[i].status != STUB_BUSID_ALLOC) &&
			    (busid_table[i].status != STUB_BUSID_REMOV))
				busid_table[i].status = STUB_BUSID_ADDED;
			ret = 0;
			spin_unlock(&busid_table[i].busid_lock);
			break;
		}
		spin_unlock(&busid_table[i].busid_lock);
	}

out:
	spin_unlock(&busid_table_lock);

	return ret;
}