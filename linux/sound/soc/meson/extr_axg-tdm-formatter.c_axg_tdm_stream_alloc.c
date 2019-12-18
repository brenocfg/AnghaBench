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
struct axg_tdm_stream {struct axg_tdm_iface* iface; int /*<<< orphan*/  lock; int /*<<< orphan*/  formatter_list; } ;
struct axg_tdm_iface {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  INIT_LIST_HEAD (int /*<<< orphan*/ *) ; 
 struct axg_tdm_stream* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mutex_init (int /*<<< orphan*/ *) ; 

struct axg_tdm_stream *axg_tdm_stream_alloc(struct axg_tdm_iface *iface)
{
	struct axg_tdm_stream *ts;

	ts = kzalloc(sizeof(*ts), GFP_KERNEL);
	if (ts) {
		INIT_LIST_HEAD(&ts->formatter_list);
		mutex_init(&ts->lock);
		ts->iface = iface;
	}

	return ts;
}