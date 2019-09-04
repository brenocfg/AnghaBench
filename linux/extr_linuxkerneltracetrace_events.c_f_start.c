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
struct seq_file {int /*<<< orphan*/  private; } ;
typedef  scalar_t__ loff_t ;

/* Variables and functions */
 int /*<<< orphan*/  ENODEV ; 
 void* ERR_PTR (int /*<<< orphan*/ ) ; 
 scalar_t__ FORMAT_HEADER ; 
 int /*<<< orphan*/  event_file_data (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  event_mutex ; 
 void* f_next (struct seq_file*,void*,scalar_t__*) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void *f_start(struct seq_file *m, loff_t *pos)
{
	void *p = (void *)FORMAT_HEADER;
	loff_t l = 0;

	/* ->stop() is called even if ->start() fails */
	mutex_lock(&event_mutex);
	if (!event_file_data(m->private))
		return ERR_PTR(-ENODEV);

	while (l < *pos && p)
		p = f_next(m, p, &l);

	return p;
}