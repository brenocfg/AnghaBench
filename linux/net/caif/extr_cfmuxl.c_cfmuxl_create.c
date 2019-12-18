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
struct cflayer {int /*<<< orphan*/  name; int /*<<< orphan*/  ctrlcmd; int /*<<< orphan*/  transmit; int /*<<< orphan*/  receive; } ;
struct cfmuxl {struct cflayer layer; int /*<<< orphan*/  receive_lock; int /*<<< orphan*/  transmit_lock; int /*<<< orphan*/  frml_list; int /*<<< orphan*/  srvl_list; } ;

/* Variables and functions */
 int /*<<< orphan*/  CAIF_LAYER_NAME_SZ ; 
 int /*<<< orphan*/  GFP_ATOMIC ; 
 int /*<<< orphan*/  INIT_LIST_HEAD (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  cfmuxl_ctrlcmd ; 
 int /*<<< orphan*/  cfmuxl_receive ; 
 int /*<<< orphan*/  cfmuxl_transmit ; 
 struct cfmuxl* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  snprintf (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  spin_lock_init (int /*<<< orphan*/ *) ; 

struct cflayer *cfmuxl_create(void)
{
	struct cfmuxl *this = kzalloc(sizeof(struct cfmuxl), GFP_ATOMIC);

	if (!this)
		return NULL;
	this->layer.receive = cfmuxl_receive;
	this->layer.transmit = cfmuxl_transmit;
	this->layer.ctrlcmd = cfmuxl_ctrlcmd;
	INIT_LIST_HEAD(&this->srvl_list);
	INIT_LIST_HEAD(&this->frml_list);
	spin_lock_init(&this->transmit_lock);
	spin_lock_init(&this->receive_lock);
	snprintf(this->layer.name, CAIF_LAYER_NAME_SZ, "mux");
	return &this->layer;
}