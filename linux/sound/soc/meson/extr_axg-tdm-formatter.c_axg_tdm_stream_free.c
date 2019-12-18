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
struct axg_tdm_stream {int /*<<< orphan*/  lock; int /*<<< orphan*/  formatter_list; } ;

/* Variables and functions */
 int /*<<< orphan*/  WARN_ON (int) ; 
 int /*<<< orphan*/  kfree (struct axg_tdm_stream*) ; 
 int /*<<< orphan*/  list_empty (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_destroy (int /*<<< orphan*/ *) ; 

void axg_tdm_stream_free(struct axg_tdm_stream *ts)
{
	/*
	 * If the list is not empty, it would mean that one of the formatter
	 * widget is still powered and attached to the interface while we
	 * we are removing the TDM DAI. It should not be possible
	 */
	WARN_ON(!list_empty(&ts->formatter_list));
	mutex_destroy(&ts->lock);
	kfree(ts);
}