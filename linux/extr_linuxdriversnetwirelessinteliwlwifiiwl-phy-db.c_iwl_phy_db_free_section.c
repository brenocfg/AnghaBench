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
typedef  int /*<<< orphan*/  u16 ;
struct iwl_phy_db_entry {scalar_t__ size; int /*<<< orphan*/ * data; } ;
struct iwl_phy_db {int dummy; } ;
typedef  enum iwl_phy_db_section_type { ____Placeholder_iwl_phy_db_section_type } iwl_phy_db_section_type ;

/* Variables and functions */
 struct iwl_phy_db_entry* iwl_phy_db_get_section (struct iwl_phy_db*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void iwl_phy_db_free_section(struct iwl_phy_db *phy_db,
				    enum iwl_phy_db_section_type type,
				    u16 chg_id)
{
	struct iwl_phy_db_entry *entry =
				iwl_phy_db_get_section(phy_db, type, chg_id);
	if (!entry)
		return;

	kfree(entry->data);
	entry->data = NULL;
	entry->size = 0;
}