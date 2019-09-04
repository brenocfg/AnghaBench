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
struct fw_event_work {int /*<<< orphan*/  refcount; } ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_ATOMIC ; 
 int /*<<< orphan*/  kref_init (int /*<<< orphan*/ *) ; 
 struct fw_event_work* kzalloc (int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static struct fw_event_work *alloc_fw_event_work(int len)
{
	struct fw_event_work *fw_event;

	fw_event = kzalloc(sizeof(*fw_event) + len, GFP_ATOMIC);
	if (!fw_event)
		return NULL;

	kref_init(&fw_event->refcount);
	return fw_event;
}