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
struct comedi_subdevice {int /*<<< orphan*/  spin_lock; struct comedi_async* async; } ;
struct comedi_buf_map {scalar_t__ n_pages; } ;
struct comedi_async {struct comedi_buf_map* buf_map; } ;

/* Variables and functions */
 int /*<<< orphan*/  comedi_buf_map_get (struct comedi_buf_map*) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

struct comedi_buf_map *
comedi_buf_map_from_subdev_get(struct comedi_subdevice *s)
{
	struct comedi_async *async = s->async;
	struct comedi_buf_map *bm = NULL;
	unsigned long flags;

	if (!async)
		return NULL;

	spin_lock_irqsave(&s->spin_lock, flags);
	bm = async->buf_map;
	/* only want it if buffer pages allocated */
	if (bm && bm->n_pages)
		comedi_buf_map_get(bm);
	else
		bm = NULL;
	spin_unlock_irqrestore(&s->spin_lock, flags);

	return bm;
}