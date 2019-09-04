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
struct zfcp_dbf_hba {int /*<<< orphan*/  id; int /*<<< orphan*/  tag; } ;
struct zfcp_dbf {int /*<<< orphan*/  hba_lock; int /*<<< orphan*/  hba; struct zfcp_dbf_hba hba_buf; } ;
struct zfcp_adapter {struct zfcp_dbf* dbf; } ;

/* Variables and functions */
 int /*<<< orphan*/  ZFCP_DBF_HBA_BASIC ; 
 int /*<<< orphan*/  ZFCP_DBF_TAG_LEN ; 
 int /*<<< orphan*/  debug_event (int /*<<< orphan*/ ,int const,struct zfcp_dbf_hba*,int) ; 
 int /*<<< orphan*/  debug_level_enabled (int /*<<< orphan*/ ,int const) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memset (struct zfcp_dbf_hba*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 scalar_t__ unlikely (int) ; 

void zfcp_dbf_hba_basic(char *tag, struct zfcp_adapter *adapter)
{
	struct zfcp_dbf *dbf = adapter->dbf;
	struct zfcp_dbf_hba *rec = &dbf->hba_buf;
	static int const level = 1;
	unsigned long flags;

	if (unlikely(!debug_level_enabled(dbf->hba, level)))
		return;

	spin_lock_irqsave(&dbf->hba_lock, flags);
	memset(rec, 0, sizeof(*rec));

	memcpy(rec->tag, tag, ZFCP_DBF_TAG_LEN);
	rec->id = ZFCP_DBF_HBA_BASIC;

	debug_event(dbf->hba, level, rec, sizeof(*rec));
	spin_unlock_irqrestore(&dbf->hba_lock, flags);
}