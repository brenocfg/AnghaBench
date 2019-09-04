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
struct cfctrl_rsp {int /*<<< orphan*/  reject_rsp; int /*<<< orphan*/  linksetup_rsp; void* radioset_rsp; void* restart_rsp; void* wake_rsp; void* sleep_rsp; int /*<<< orphan*/  linkdestroy_rsp; void* linkerror_ind; int /*<<< orphan*/  enum_rsp; } ;
struct cfcnfg {struct cfcnfg* ctrl; struct cfcnfg* mux; int /*<<< orphan*/  lock; int /*<<< orphan*/  phys; } ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_ATOMIC ; 
 int /*<<< orphan*/  INIT_LIST_HEAD (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  cfcnfg_linkdestroy_rsp ; 
 int /*<<< orphan*/  cfcnfg_linkup_rsp ; 
 int /*<<< orphan*/  cfcnfg_reject_rsp ; 
 struct cfcnfg* cfctrl_create () ; 
 int /*<<< orphan*/  cfctrl_enum_resp ; 
 struct cfctrl_rsp* cfctrl_get_respfuncs (struct cfcnfg*) ; 
 void* cfctrl_resp_func ; 
 struct cfcnfg* cfmuxl_create () ; 
 int /*<<< orphan*/  cfmuxl_set_uplayer (struct cfcnfg*,struct cfcnfg*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree (struct cfcnfg*) ; 
 struct cfcnfg* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  layer_set_dn (struct cfcnfg*,struct cfcnfg*) ; 
 int /*<<< orphan*/  layer_set_up (struct cfcnfg*,struct cfcnfg*) ; 
 int /*<<< orphan*/  might_sleep () ; 
 int /*<<< orphan*/  mutex_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  synchronize_rcu () ; 

struct cfcnfg *cfcnfg_create(void)
{
	struct cfcnfg *this;
	struct cfctrl_rsp *resp;

	might_sleep();

	/* Initiate this layer */
	this = kzalloc(sizeof(struct cfcnfg), GFP_ATOMIC);
	if (!this)
		return NULL;
	this->mux = cfmuxl_create();
	if (!this->mux)
		goto out_of_mem;
	this->ctrl = cfctrl_create();
	if (!this->ctrl)
		goto out_of_mem;
	/* Initiate response functions */
	resp = cfctrl_get_respfuncs(this->ctrl);
	resp->enum_rsp = cfctrl_enum_resp;
	resp->linkerror_ind = cfctrl_resp_func;
	resp->linkdestroy_rsp = cfcnfg_linkdestroy_rsp;
	resp->sleep_rsp = cfctrl_resp_func;
	resp->wake_rsp = cfctrl_resp_func;
	resp->restart_rsp = cfctrl_resp_func;
	resp->radioset_rsp = cfctrl_resp_func;
	resp->linksetup_rsp = cfcnfg_linkup_rsp;
	resp->reject_rsp = cfcnfg_reject_rsp;
	INIT_LIST_HEAD(&this->phys);

	cfmuxl_set_uplayer(this->mux, this->ctrl, 0);
	layer_set_dn(this->ctrl, this->mux);
	layer_set_up(this->ctrl, this);
	mutex_init(&this->lock);

	return this;
out_of_mem:
	synchronize_rcu();

	kfree(this->mux);
	kfree(this->ctrl);
	kfree(this);
	return NULL;
}