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
struct axg_tdm_stream {int /*<<< orphan*/  lock; } ;
struct axg_tdm_formatter {int /*<<< orphan*/  list; struct axg_tdm_stream* stream; } ;

/* Variables and functions */
 int /*<<< orphan*/  axg_tdm_formatter_disable (struct axg_tdm_formatter*) ; 
 int /*<<< orphan*/  list_del (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void axg_tdm_formatter_dettach(struct axg_tdm_formatter *formatter)
{
	struct axg_tdm_stream *ts = formatter->stream;

	mutex_lock(&ts->lock);
	list_del(&formatter->list);
	mutex_unlock(&ts->lock);

	axg_tdm_formatter_disable(formatter);
}