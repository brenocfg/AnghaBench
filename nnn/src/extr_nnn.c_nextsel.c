#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int uint ;
struct kevent {int dummy; } ;
struct inotify_event {int len; int wd; int mask; } ;
struct TYPE_5__ {int sym; int act; } ;
struct TYPE_4__ {int /*<<< orphan*/  blkorder; int /*<<< orphan*/  selmode; scalar_t__ filtermode; } ;

/* Variables and functions */
 int CONTROL (char) ; 
 int /*<<< orphan*/  DPRINTF_D (int) ; 
 int /*<<< orphan*/  DPRINTF_S (char*) ; 
 int EVENT_BUF_LEN ; 
 int FILTER ; 
 int INOTIFY_MASK ; 
 int LEN (TYPE_2__*) ; 
 int MSGWAIT ; 
 int /*<<< orphan*/  NUM_EVENT_FDS ; 
 int NUM_EVENT_SLOTS ; 
 TYPE_2__* bindings ; 
 TYPE_1__ cfg ; 
 scalar_t__ event_fd ; 
 int /*<<< orphan*/  events_to_monitor ; 
 int getch () ; 
 int /*<<< orphan*/  gtimeout ; 
 int idle ; 
 int /*<<< orphan*/  inotify_fd ; 
 scalar_t__ inotify_wd ; 
 scalar_t__ kevent (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,struct kevent*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  kq ; 
 int /*<<< orphan*/  memset (void*,int,int) ; 
 int read (int /*<<< orphan*/ ,char*,int) ; 

__attribute__((used)) static int nextsel(int presel)
{
	int c = presel;
	uint i;
	const uint len = LEN(bindings);
#ifdef LINUX_INOTIFY
	struct inotify_event *event;
	char inotify_buf[EVENT_BUF_LEN];

	memset((void *)inotify_buf, 0x0, EVENT_BUF_LEN);
#elif defined(BSD_KQUEUE)
	struct kevent event_data[NUM_EVENT_SLOTS];

	memset((void *)event_data, 0x0, sizeof(struct kevent) * NUM_EVENT_SLOTS);
#endif

	if (c == 0 || c == MSGWAIT) {
		c = getch();
		DPRINTF_D(c);

		if (presel == MSGWAIT) {
			if (cfg.filtermode)
				c = FILTER;
			else
				c = CONTROL('L');
		}
	}

	if (c == -1) {
		++idle;

		/*
		 * Do not check for directory changes in du mode.
		 * A redraw forces du calculation.
		 * Check for changes every odd second.
		 */
#ifdef LINUX_INOTIFY
		if (!cfg.selmode && !cfg.blkorder && inotify_wd >= 0 && (idle & 1)) {
			i = read(inotify_fd, inotify_buf, EVENT_BUF_LEN);
			if (i > 0) {
				char *ptr;

				for (ptr = inotify_buf;
				     ptr + ((struct inotify_event *)ptr)->len < inotify_buf + i;
				     ptr += sizeof(struct inotify_event) + event->len) {
					event = (struct inotify_event *) ptr;
					DPRINTF_D(event->wd);
					DPRINTF_D(event->mask);
					if (!event->wd)
						break;

					if (event->mask & INOTIFY_MASK) {
						c = CONTROL('L');
						DPRINTF_S("issue refresh");
						break;
					}
				}
				DPRINTF_S("inotify read done");
			}
		}
#elif defined(BSD_KQUEUE)
		if (!cfg.selmode && !cfg.blkorder && event_fd >= 0 && idle & 1
		    && kevent(kq, events_to_monitor, NUM_EVENT_SLOTS,
			      event_data, NUM_EVENT_FDS, &gtimeout) > 0)
			c = CONTROL('L');
#endif
	} else
		idle = 0;

	for (i = 0; i < len; ++i)
		if (c == bindings[i].sym)
			return bindings[i].act;

	return 0;
}