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
typedef  int /*<<< orphan*/  u32 ;
struct TYPE_2__ {int ale_entries; } ;
struct cpsw_ale {TYPE_1__ params; } ;

/* Variables and functions */
 int ALE_ENTRY_WORDS ; 
 int ALE_TYPE_FREE ; 
 int ENOENT ; 
 int cpsw_ale_get_entry_type (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  cpsw_ale_read (struct cpsw_ale*,int,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int cpsw_ale_match_free(struct cpsw_ale *ale)
{
	u32 ale_entry[ALE_ENTRY_WORDS];
	int type, idx;

	for (idx = 0; idx < ale->params.ale_entries; idx++) {
		cpsw_ale_read(ale, idx, ale_entry);
		type = cpsw_ale_get_entry_type(ale_entry);
		if (type == ALE_TYPE_FREE)
			return idx;
	}
	return -ENOENT;
}