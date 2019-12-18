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
struct fanotify_event {scalar_t__ fh_type; } ;

/* Variables and functions */
 scalar_t__ FILEID_INVALID ; 
 scalar_t__ FILEID_ROOT ; 

__attribute__((used)) static inline bool fanotify_event_has_fid(struct fanotify_event *event)
{
	return event->fh_type != FILEID_ROOT &&
		event->fh_type != FILEID_INVALID;
}