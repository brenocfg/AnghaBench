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
struct chp_id {int /*<<< orphan*/  id; int /*<<< orphan*/  cssid; } ;

/* Variables and functions */
 int /*<<< orphan*/  CIO_MSG_EVENT (int,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ cfg_deconfigure ; 
 scalar_t__ cfg_get_task (struct chp_id) ; 
 int /*<<< orphan*/  cfg_lock ; 
 int /*<<< orphan*/  cfg_none ; 
 int /*<<< orphan*/  cfg_set_task (struct chp_id,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 

void chp_cfg_cancel_deconfigure(struct chp_id chpid)
{
	CIO_MSG_EVENT(2, "chp_cfg_cancel:%x.%02x\n", chpid.cssid, chpid.id);
	spin_lock(&cfg_lock);
	if (cfg_get_task(chpid) == cfg_deconfigure)
		cfg_set_task(chpid, cfg_none);
	spin_unlock(&cfg_lock);
}