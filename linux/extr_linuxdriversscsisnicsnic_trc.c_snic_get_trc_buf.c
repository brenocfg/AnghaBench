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
struct snic_trc_data {scalar_t__ ts; } ;
struct snic_trc {size_t wr_idx; size_t max_idx; size_t rd_idx; int /*<<< orphan*/  lock; struct snic_trc_data* buf; } ;
struct TYPE_2__ {struct snic_trc trc; } ;

/* Variables and functions */
 TYPE_1__* snic_glob ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

struct snic_trc_data *
snic_get_trc_buf(void)
{
	struct snic_trc *trc = &snic_glob->trc;
	struct snic_trc_data *td = NULL;
	unsigned long flags;

	spin_lock_irqsave(&trc->lock, flags);
	td = &trc->buf[trc->wr_idx];
	trc->wr_idx++;

	if (trc->wr_idx == trc->max_idx)
		trc->wr_idx = 0;

	if (trc->wr_idx != trc->rd_idx) {
		spin_unlock_irqrestore(&trc->lock, flags);

		goto end;
	}

	trc->rd_idx++;
	if (trc->rd_idx == trc->max_idx)
		trc->rd_idx = 0;

	td->ts = 0;	/* Marker for checking the record, for complete data*/
	spin_unlock_irqrestore(&trc->lock, flags);

end:

	return td;
}