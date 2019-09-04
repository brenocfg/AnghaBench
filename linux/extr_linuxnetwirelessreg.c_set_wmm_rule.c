#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct ieee80211_wmm_rule {TYPE_3__* ap; TYPE_1__* client; } ;
struct ieee80211_reg_rule {int has_wmm; struct ieee80211_wmm_rule wmm_rule; } ;
struct fwdb_wmm_rule {TYPE_4__* ap; TYPE_2__* client; } ;
struct TYPE_8__ {int ecw; int /*<<< orphan*/  cot; int /*<<< orphan*/  aifsn; } ;
struct TYPE_7__ {int cot; int /*<<< orphan*/  aifsn; void* cw_max; void* cw_min; } ;
struct TYPE_6__ {int ecw; int /*<<< orphan*/  cot; int /*<<< orphan*/  aifsn; } ;
struct TYPE_5__ {int cot; int /*<<< orphan*/  aifsn; void* cw_max; void* cw_min; } ;

/* Variables and functions */
 unsigned int IEEE80211_NUM_ACS ; 
 int be16_to_cpu (int /*<<< orphan*/ ) ; 
 void* ecw2cw (int) ; 

__attribute__((used)) static void set_wmm_rule(struct ieee80211_reg_rule *rrule,
			 struct fwdb_wmm_rule *wmm)
{
	struct ieee80211_wmm_rule *rule = &rrule->wmm_rule;
	unsigned int i;

	for (i = 0; i < IEEE80211_NUM_ACS; i++) {
		rule->client[i].cw_min =
			ecw2cw((wmm->client[i].ecw & 0xf0) >> 4);
		rule->client[i].cw_max = ecw2cw(wmm->client[i].ecw & 0x0f);
		rule->client[i].aifsn =  wmm->client[i].aifsn;
		rule->client[i].cot = 1000 * be16_to_cpu(wmm->client[i].cot);
		rule->ap[i].cw_min = ecw2cw((wmm->ap[i].ecw & 0xf0) >> 4);
		rule->ap[i].cw_max = ecw2cw(wmm->ap[i].ecw & 0x0f);
		rule->ap[i].aifsn = wmm->ap[i].aifsn;
		rule->ap[i].cot = 1000 * be16_to_cpu(wmm->ap[i].cot);
	}

	rrule->has_wmm = true;
}