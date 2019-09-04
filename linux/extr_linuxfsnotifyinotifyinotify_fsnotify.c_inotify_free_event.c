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
struct fsnotify_event {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  INOTIFY_E (struct fsnotify_event*) ; 
 int /*<<< orphan*/  kfree (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void inotify_free_event(struct fsnotify_event *fsn_event)
{
	kfree(INOTIFY_E(fsn_event));
}