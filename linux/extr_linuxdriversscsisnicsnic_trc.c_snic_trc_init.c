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
struct snic_trc_data {int dummy; } ;
struct snic_trc {int max_idx; int enable; scalar_t__ wr_idx; scalar_t__ rd_idx; int /*<<< orphan*/  lock; struct snic_trc_data* buf; } ;
struct TYPE_2__ {struct snic_trc trc; } ;

/* Variables and functions */
 int ENOMEM ; 
 int PAGE_SIZE ; 
 int /*<<< orphan*/  SNIC_ERR (char*,...) ; 
 int /*<<< orphan*/  SNIC_INFO (char*,int) ; 
 int SNIC_TRC_ENTRY_SZ ; 
 int /*<<< orphan*/  memset (void*,int /*<<< orphan*/ ,int) ; 
 TYPE_1__* snic_glob ; 
 int snic_trace_max_pages ; 
 int snic_trc_debugfs_init () ; 
 int /*<<< orphan*/  snic_trc_free () ; 
 int /*<<< orphan*/  spin_lock_init (int /*<<< orphan*/ *) ; 
 void* vmalloc (int) ; 

int
snic_trc_init(void)
{
	struct snic_trc *trc = &snic_glob->trc;
	void *tbuf = NULL;
	int tbuf_sz = 0, ret;

	tbuf_sz = (snic_trace_max_pages * PAGE_SIZE);
	tbuf = vmalloc(tbuf_sz);
	if (!tbuf) {
		SNIC_ERR("Failed to Allocate Trace Buffer Size. %d\n", tbuf_sz);
		SNIC_ERR("Trace Facility not enabled.\n");
		ret = -ENOMEM;

		return ret;
	}

	memset(tbuf, 0, tbuf_sz);
	trc->buf = (struct snic_trc_data *) tbuf;
	spin_lock_init(&trc->lock);

	ret = snic_trc_debugfs_init();
	if (ret) {
		SNIC_ERR("Failed to create Debugfs Files.\n");

		goto error;
	}

	trc->max_idx = (tbuf_sz / SNIC_TRC_ENTRY_SZ);
	trc->rd_idx = trc->wr_idx = 0;
	trc->enable = true;
	SNIC_INFO("Trace Facility Enabled.\n Trace Buffer SZ %lu Pages.\n",
		  tbuf_sz / PAGE_SIZE);
	ret = 0;

	return ret;

error:
	snic_trc_free();

	return ret;
}