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
struct inotify_event_info {scalar_t__ name_len; } ;
struct inotify_event {int dummy; } ;
struct fsnotify_event {int dummy; } ;

/* Variables and functions */
 struct inotify_event_info* INOTIFY_E (struct fsnotify_event*) ; 
 int roundup (scalar_t__,int) ; 

__attribute__((used)) static int round_event_name_len(struct fsnotify_event *fsn_event)
{
	struct inotify_event_info *event;

	event = INOTIFY_E(fsn_event);
	if (!event->name_len)
		return 0;
	return roundup(event->name_len + 1, sizeof(struct inotify_event));
}