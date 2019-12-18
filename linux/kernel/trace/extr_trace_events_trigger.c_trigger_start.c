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
struct trace_event_file {int /*<<< orphan*/  triggers; } ;
struct seq_file {int /*<<< orphan*/  private; } ;
typedef  int /*<<< orphan*/  loff_t ;

/* Variables and functions */
 int /*<<< orphan*/  ENODEV ; 
 void* ERR_PTR (int /*<<< orphan*/ ) ; 
 void* SHOW_AVAILABLE_TRIGGERS ; 
 struct trace_event_file* event_file_data (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  event_mutex ; 
 scalar_t__ list_empty (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 void* seq_list_start (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 scalar_t__ unlikely (int) ; 

__attribute__((used)) static void *trigger_start(struct seq_file *m, loff_t *pos)
{
	struct trace_event_file *event_file;

	/* ->stop() is called even if ->start() fails */
	mutex_lock(&event_mutex);
	event_file = event_file_data(m->private);
	if (unlikely(!event_file))
		return ERR_PTR(-ENODEV);

	if (list_empty(&event_file->triggers))
		return *pos == 0 ? SHOW_AVAILABLE_TRIGGERS : NULL;

	return seq_list_start(&event_file->triggers, *pos);
}