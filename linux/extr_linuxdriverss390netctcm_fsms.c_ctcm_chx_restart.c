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
struct net_device {int /*<<< orphan*/  name; } ;
struct channel {int /*<<< orphan*/  timer; int /*<<< orphan*/  cdev; int /*<<< orphan*/  id; struct net_device* netdev; } ;
typedef  int /*<<< orphan*/  fsm_instance ;

/* Variables and functions */
 int /*<<< orphan*/  CTCM_DBF_TEXT_ (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  CTCM_FUNTAIL ; 
 int /*<<< orphan*/  CTCM_TIME_5_SEC ; 
 int /*<<< orphan*/  CTC_DBF_NOTICE ; 
 int CTC_EVENT_TIMER ; 
 int CTC_STATE_STARTWAIT ; 
 int EBUSY ; 
 int /*<<< orphan*/  TRACE ; 
 int ccw_device_halt (int /*<<< orphan*/ ,unsigned long) ; 
 int /*<<< orphan*/  ctcm_ccw_check_rc (struct channel*,int,char*) ; 
 int /*<<< orphan*/  fsm_addtimer (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int,struct channel*) ; 
 int /*<<< orphan*/  fsm_deltimer (int /*<<< orphan*/ *) ; 
 int fsm_getstate (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  fsm_newstate (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  get_ccwdev_lock (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ ,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ ,unsigned long) ; 

__attribute__((used)) static void ctcm_chx_restart(fsm_instance *fi, int event, void *arg)
{
	struct channel *ch = arg;
	struct net_device *dev = ch->netdev;
	unsigned long saveflags = 0;
	int oldstate;
	int rc;

	CTCM_DBF_TEXT_(TRACE, CTC_DBF_NOTICE,
		"%s: %s[%d] of %s\n",
			CTCM_FUNTAIL, ch->id, event, dev->name);

	fsm_deltimer(&ch->timer);

	fsm_addtimer(&ch->timer, CTCM_TIME_5_SEC, CTC_EVENT_TIMER, ch);
	oldstate = fsm_getstate(fi);
	fsm_newstate(fi, CTC_STATE_STARTWAIT);
	if (event == CTC_EVENT_TIMER)	/* only for timer not yet locked */
		spin_lock_irqsave(get_ccwdev_lock(ch->cdev), saveflags);
			/* Such conditional locking is a known problem for
			 * sparse because its undeterministic in static view.
			 * Warnings should be ignored here. */
	rc = ccw_device_halt(ch->cdev, (unsigned long)ch);
	if (event == CTC_EVENT_TIMER)
		spin_unlock_irqrestore(get_ccwdev_lock(ch->cdev), saveflags);
	if (rc != 0) {
		if (rc != -EBUSY) {
		    fsm_deltimer(&ch->timer);
		    fsm_newstate(fi, oldstate);
		}
		ctcm_ccw_check_rc(ch, rc, "HaltIO in ctcm_chx_restart");
	}
}