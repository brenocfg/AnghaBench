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
typedef  int u16 ;
struct TYPE_2__ {scalar_t__ inuse_cnt; scalar_t__ count; scalar_t__ tail; scalar_t__ head; } ;
struct rio_channel {int id; TYPE_1__ rx_ring; int /*<<< orphan*/  ref; int /*<<< orphan*/  comp_close; int /*<<< orphan*/  comp; int /*<<< orphan*/  ch_node; int /*<<< orphan*/  accept_queue; int /*<<< orphan*/  lock; int /*<<< orphan*/  state; } ;

/* Variables and functions */
 int EBUSY ; 
 int ENOMEM ; 
 int ENOSPC ; 
 struct rio_channel* ERR_PTR (int) ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  GFP_NOWAIT ; 
 int /*<<< orphan*/  INIT_LIST_HEAD (int /*<<< orphan*/ *) ; 
 int RIOCM_MAX_CHNUM ; 
 int /*<<< orphan*/  RIO_CM_IDLE ; 
 int /*<<< orphan*/  ch_idr ; 
 int chstart ; 
 int idr_alloc_cyclic (int /*<<< orphan*/ *,struct rio_channel*,int,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  idr_lock ; 
 int /*<<< orphan*/  idr_preload (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  idr_preload_end () ; 
 int /*<<< orphan*/  init_completion (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  kfree (struct rio_channel*) ; 
 int /*<<< orphan*/  kref_init (int /*<<< orphan*/ *) ; 
 struct rio_channel* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock_bh (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_bh (int /*<<< orphan*/ *) ; 

__attribute__((used)) static struct rio_channel *riocm_ch_alloc(u16 ch_num)
{
	int id;
	int start, end;
	struct rio_channel *ch;

	ch = kzalloc(sizeof(*ch), GFP_KERNEL);
	if (!ch)
		return ERR_PTR(-ENOMEM);

	if (ch_num) {
		/* If requested, try to obtain the specified channel ID */
		start = ch_num;
		end = ch_num + 1;
	} else {
		/* Obtain channel ID from the dynamic allocation range */
		start = chstart;
		end = RIOCM_MAX_CHNUM + 1;
	}

	idr_preload(GFP_KERNEL);
	spin_lock_bh(&idr_lock);
	id = idr_alloc_cyclic(&ch_idr, ch, start, end, GFP_NOWAIT);
	spin_unlock_bh(&idr_lock);
	idr_preload_end();

	if (id < 0) {
		kfree(ch);
		return ERR_PTR(id == -ENOSPC ? -EBUSY : id);
	}

	ch->id = (u16)id;
	ch->state = RIO_CM_IDLE;
	spin_lock_init(&ch->lock);
	INIT_LIST_HEAD(&ch->accept_queue);
	INIT_LIST_HEAD(&ch->ch_node);
	init_completion(&ch->comp);
	init_completion(&ch->comp_close);
	kref_init(&ch->ref);
	ch->rx_ring.head = 0;
	ch->rx_ring.tail = 0;
	ch->rx_ring.count = 0;
	ch->rx_ring.inuse_cnt = 0;

	return ch;
}