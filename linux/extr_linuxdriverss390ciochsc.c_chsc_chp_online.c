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
struct chp_id {int cssid; int id; } ;
struct chp_link {struct chp_id chpid; } ;
struct channel_path {int /*<<< orphan*/  lock; } ;

/* Variables and functions */
 int /*<<< orphan*/  CIO_TRACE_EVENT (int,char*) ; 
 int /*<<< orphan*/  __s390_process_res_acc ; 
 scalar_t__ chp_get_status (struct chp_id) ; 
 int /*<<< orphan*/  chp_update_desc (struct channel_path*) ; 
 struct channel_path* chpid_to_chp (struct chp_id) ; 
 int /*<<< orphan*/  css_schedule_reprobe () ; 
 int /*<<< orphan*/  css_wait_for_slow_path () ; 
 int /*<<< orphan*/  for_each_subchannel_staged (int /*<<< orphan*/ ,int /*<<< orphan*/ *,struct chp_link*) ; 
 int /*<<< orphan*/  memset (struct chp_link*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sprintf (char*,char*,int,int) ; 

void chsc_chp_online(struct chp_id chpid)
{
	struct channel_path *chp = chpid_to_chp(chpid);
	struct chp_link link;
	char dbf_txt[15];

	sprintf(dbf_txt, "cadd%x.%02x", chpid.cssid, chpid.id);
	CIO_TRACE_EVENT(2, dbf_txt);

	if (chp_get_status(chpid) != 0) {
		memset(&link, 0, sizeof(struct chp_link));
		link.chpid = chpid;
		/* Wait until previous actions have settled. */
		css_wait_for_slow_path();

		mutex_lock(&chp->lock);
		chp_update_desc(chp);
		mutex_unlock(&chp->lock);

		for_each_subchannel_staged(__s390_process_res_acc, NULL,
					   &link);
		css_schedule_reprobe();
	}
}