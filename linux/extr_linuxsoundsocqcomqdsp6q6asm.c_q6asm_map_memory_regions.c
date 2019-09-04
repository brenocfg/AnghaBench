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
struct audio_client {TYPE_1__* port; int /*<<< orphan*/  dev; int /*<<< orphan*/  lock; } ;
struct audio_buffer {size_t size; scalar_t__ phys; } ;
typedef  scalar_t__ phys_addr_t ;
struct TYPE_2__ {unsigned int num_periods; struct audio_buffer* buf; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_ATOMIC ; 
 int __q6asm_memory_map_regions (struct audio_client*,unsigned int,size_t,unsigned int,int) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*) ; 
 struct audio_buffer* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  q6asm_audio_client_free_buf (struct audio_client*,TYPE_1__*) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

int q6asm_map_memory_regions(unsigned int dir, struct audio_client *ac,
			     phys_addr_t phys,
			     size_t period_sz, unsigned int periods)
{
	struct audio_buffer *buf;
	unsigned long flags;
	int cnt;
	int rc;

	spin_lock_irqsave(&ac->lock, flags);
	if (ac->port[dir].buf) {
		dev_err(ac->dev, "Buffer already allocated\n");
		spin_unlock_irqrestore(&ac->lock, flags);
		return 0;
	}

	buf = kzalloc(((sizeof(struct audio_buffer)) * periods), GFP_ATOMIC);
	if (!buf) {
		spin_unlock_irqrestore(&ac->lock, flags);
		return -ENOMEM;
	}


	ac->port[dir].buf = buf;

	buf[0].phys = phys;
	buf[0].size = period_sz;

	for (cnt = 1; cnt < periods; cnt++) {
		if (period_sz > 0) {
			buf[cnt].phys = buf[0].phys + (cnt * period_sz);
			buf[cnt].size = period_sz;
		}
	}
	ac->port[dir].num_periods = periods;

	spin_unlock_irqrestore(&ac->lock, flags);

	rc = __q6asm_memory_map_regions(ac, dir, period_sz, periods, 1);
	if (rc < 0) {
		dev_err(ac->dev, "Memory_map_regions failed\n");
		q6asm_audio_client_free_buf(ac, &ac->port[dir]);
	}

	return rc;
}