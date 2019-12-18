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
struct fanotify_event {scalar_t__ fh_len; } ;

/* Variables and functions */
 scalar_t__ FANOTIFY_INLINE_FH_LEN ; 
 scalar_t__ fanotify_event_has_fid (struct fanotify_event*) ; 

__attribute__((used)) static inline bool fanotify_event_has_ext_fh(struct fanotify_event *event)
{
	return fanotify_event_has_fid(event) &&
		event->fh_len > FANOTIFY_INLINE_FH_LEN;
}