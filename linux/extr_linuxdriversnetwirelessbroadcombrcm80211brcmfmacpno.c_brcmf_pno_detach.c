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
struct brcmf_pno_info {int /*<<< orphan*/  req_lock; int /*<<< orphan*/  n_reqs; } ;
struct brcmf_cfg80211_info {struct brcmf_pno_info* pno; } ;

/* Variables and functions */
 int /*<<< orphan*/  TRACE ; 
 int /*<<< orphan*/  WARN_ON (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  brcmf_dbg (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  kfree (struct brcmf_pno_info*) ; 
 int /*<<< orphan*/  mutex_destroy (int /*<<< orphan*/ *) ; 

void brcmf_pno_detach(struct brcmf_cfg80211_info *cfg)
{
	struct brcmf_pno_info *pi;

	brcmf_dbg(TRACE, "enter\n");
	pi = cfg->pno;
	cfg->pno = NULL;

	WARN_ON(pi->n_reqs);
	mutex_destroy(&pi->req_lock);
	kfree(pi);
}