#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {int enabled; } ;
struct airo_info {int /*<<< orphan*/  tfm; TYPE_2__* mod; TYPE_1__ micstats; int /*<<< orphan*/  sem; int /*<<< orphan*/  jobs; } ;
typedef  int /*<<< orphan*/  mic_rid ;
struct TYPE_10__ {scalar_t__ valid; } ;
struct TYPE_9__ {int /*<<< orphan*/  unicast; scalar_t__ unicastValid; int /*<<< orphan*/  multicast; scalar_t__ multicastValid; int /*<<< orphan*/  state; } ;
struct TYPE_8__ {TYPE_4__ uCtx; TYPE_4__ mCtx; } ;
typedef  TYPE_3__ MICRid ;

/* Variables and functions */
 int /*<<< orphan*/  JOB_MIC ; 
 int /*<<< orphan*/  PC4500_readrid (struct airo_info*,int /*<<< orphan*/ ,TYPE_3__*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  RID_MIC ; 
 int /*<<< orphan*/  age_mic_context (TYPE_4__*,TYPE_4__*,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  clear_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int le16_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  up (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void micinit(struct airo_info *ai)
{
	MICRid mic_rid;

	clear_bit(JOB_MIC, &ai->jobs);
	PC4500_readrid(ai, RID_MIC, &mic_rid, sizeof(mic_rid), 0);
	up(&ai->sem);

	ai->micstats.enabled = (le16_to_cpu(mic_rid.state) & 0x00FF) ? 1 : 0;
	if (!ai->micstats.enabled) {
		/* So next time we have a valid key and mic is enabled, we will
		 * update the sequence number if the key is the same as before.
		 */
		ai->mod[0].uCtx.valid = 0;
		ai->mod[0].mCtx.valid = 0;
		return;
	}

	if (mic_rid.multicastValid) {
		age_mic_context(&ai->mod[0].mCtx, &ai->mod[1].mCtx,
		                mic_rid.multicast, sizeof(mic_rid.multicast),
		                ai->tfm);
	}

	if (mic_rid.unicastValid) {
		age_mic_context(&ai->mod[0].uCtx, &ai->mod[1].uCtx,
				mic_rid.unicast, sizeof(mic_rid.unicast),
				ai->tfm);
	}
}