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
struct fanotify_event {int /*<<< orphan*/  fh_len; int /*<<< orphan*/  fid; } ;

/* Variables and functions */
 void* fanotify_fid_fh (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline void *fanotify_event_fh(struct fanotify_event *event)
{
	return fanotify_fid_fh(&event->fid, event->fh_len);
}