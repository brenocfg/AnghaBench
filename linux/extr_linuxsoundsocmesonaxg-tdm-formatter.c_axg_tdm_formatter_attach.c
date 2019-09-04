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
struct axg_tdm_stream {int /*<<< orphan*/  lock; int /*<<< orphan*/  formatter_list; scalar_t__ ready; } ;
struct axg_tdm_formatter {int /*<<< orphan*/  list; struct axg_tdm_stream* stream; } ;

/* Variables and functions */
 int axg_tdm_formatter_enable (struct axg_tdm_formatter*) ; 
 int /*<<< orphan*/  list_add_tail (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pr_err (char*) ; 

__attribute__((used)) static int axg_tdm_formatter_attach(struct axg_tdm_formatter *formatter)
{
	struct axg_tdm_stream *ts = formatter->stream;
	int ret = 0;

	mutex_lock(&ts->lock);

	/* Catch up if the stream is already running when we attach */
	if (ts->ready) {
		ret = axg_tdm_formatter_enable(formatter);
		if (ret) {
			pr_err("failed to enable formatter\n");
			goto out;
		}
	}

	list_add_tail(&formatter->list, &ts->formatter_list);
out:
	mutex_unlock(&ts->lock);
	return ret;
}