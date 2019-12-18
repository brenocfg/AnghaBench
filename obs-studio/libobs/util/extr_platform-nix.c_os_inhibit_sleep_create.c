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
struct os_inhibit_info {int /*<<< orphan*/  reason; int /*<<< orphan*/  attr; int /*<<< orphan*/  stop_event; int /*<<< orphan*/  dbus; } ;
typedef  int /*<<< orphan*/  sigset_t ;
typedef  struct os_inhibit_info os_inhibit_t ;

/* Variables and functions */
 int /*<<< orphan*/  OS_EVENT_TYPE_AUTO ; 
 int POSIX_SPAWN_SETSIGDEF ; 
 int POSIX_SPAWN_SETSIGMASK ; 
 int /*<<< orphan*/  SIGPIPE ; 
 int /*<<< orphan*/  bstrdup (char const*) ; 
 struct os_inhibit_info* bzalloc (int) ; 
 int /*<<< orphan*/  dbus_sleep_info_create () ; 
 int /*<<< orphan*/  os_event_init (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  posix_spawnattr_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  posix_spawnattr_setflags (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  posix_spawnattr_setsigdefault (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  posix_spawnattr_setsigmask (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sigaddset (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sigemptyset (int /*<<< orphan*/ *) ; 

os_inhibit_t *os_inhibit_sleep_create(const char *reason)
{
	struct os_inhibit_info *info = bzalloc(sizeof(*info));
	sigset_t set;

#if HAVE_DBUS
	info->dbus = dbus_sleep_info_create();
#endif

	os_event_init(&info->stop_event, OS_EVENT_TYPE_AUTO);
	posix_spawnattr_init(&info->attr);

	sigemptyset(&set);
	posix_spawnattr_setsigmask(&info->attr, &set);
	sigaddset(&set, SIGPIPE);
	posix_spawnattr_setsigdefault(&info->attr, &set);
	posix_spawnattr_setflags(&info->attr, POSIX_SPAWN_SETSIGDEF |
						      POSIX_SPAWN_SETSIGMASK);

	info->reason = bstrdup(reason);
	return info;
}