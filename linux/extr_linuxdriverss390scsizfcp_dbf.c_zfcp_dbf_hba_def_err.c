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
typedef  int /*<<< orphan*/  u64 ;
typedef  int u16 ;
struct zfcp_dbf_pay {int counter; int /*<<< orphan*/  data; int /*<<< orphan*/  fsf_req_id; int /*<<< orphan*/  area; } ;
struct zfcp_dbf {int /*<<< orphan*/  pay_lock; int /*<<< orphan*/  pay; struct zfcp_dbf_pay pay_buf; } ;
struct zfcp_adapter {struct zfcp_dbf* dbf; } ;
struct qdio_buffer {int dummy; } ;

/* Variables and functions */
 scalar_t__ ZFCP_DBF_PAY_MAX_REC ; 
 int /*<<< orphan*/  debug_event (int /*<<< orphan*/ ,int const,struct zfcp_dbf_pay*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  debug_level_enabled (int /*<<< orphan*/ ,int const) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  memset (struct zfcp_dbf_pay*,int /*<<< orphan*/ ,int) ; 
 int min (int,int) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 scalar_t__ unlikely (int) ; 
 int /*<<< orphan*/  zfcp_dbf_plen (int) ; 

void zfcp_dbf_hba_def_err(struct zfcp_adapter *adapter, u64 req_id, u16 scount,
			  void **pl)
{
	struct zfcp_dbf *dbf = adapter->dbf;
	struct zfcp_dbf_pay *payload = &dbf->pay_buf;
	unsigned long flags;
	static int const level = 1;
	u16 length;

	if (unlikely(!debug_level_enabled(dbf->pay, level)))
		return;

	if (!pl)
		return;

	spin_lock_irqsave(&dbf->pay_lock, flags);
	memset(payload, 0, sizeof(*payload));

	memcpy(payload->area, "def_err", 7);
	payload->fsf_req_id = req_id;
	payload->counter = 0;
	length = min((u16)sizeof(struct qdio_buffer),
		     (u16)ZFCP_DBF_PAY_MAX_REC);

	while (payload->counter < scount && (char *)pl[payload->counter]) {
		memcpy(payload->data, (char *)pl[payload->counter], length);
		debug_event(dbf->pay, level, payload, zfcp_dbf_plen(length));
		payload->counter++;
	}

	spin_unlock_irqrestore(&dbf->pay_lock, flags);
}