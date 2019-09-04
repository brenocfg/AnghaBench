#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct gsm_mux {struct gsm_dlci** dlci; int /*<<< orphan*/  adaption; } ;
struct TYPE_2__ {int /*<<< orphan*/ * ops; } ;
struct gsm_dlci {int addr; int /*<<< orphan*/  data; int /*<<< orphan*/  state; int /*<<< orphan*/  adaption; struct gsm_mux* gsm; TYPE_1__ port; int /*<<< orphan*/  t1; int /*<<< orphan*/  skb_list; int /*<<< orphan*/  _fifo; int /*<<< orphan*/ * fifo; int /*<<< orphan*/  mutex; int /*<<< orphan*/  lock; } ;

/* Variables and functions */
 int /*<<< orphan*/  DLCI_CLOSED ; 
 int /*<<< orphan*/  GFP_ATOMIC ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  gsm_dlci_command ; 
 int /*<<< orphan*/  gsm_dlci_data ; 
 int /*<<< orphan*/  gsm_dlci_t1 ; 
 int /*<<< orphan*/  gsm_port_ops ; 
 scalar_t__ kfifo_alloc (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree (struct gsm_dlci*) ; 
 struct gsm_dlci* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mutex_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  skb_queue_head_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  timer_setup (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tty_port_init (TYPE_1__*) ; 

__attribute__((used)) static struct gsm_dlci *gsm_dlci_alloc(struct gsm_mux *gsm, int addr)
{
	struct gsm_dlci *dlci = kzalloc(sizeof(struct gsm_dlci), GFP_ATOMIC);
	if (dlci == NULL)
		return NULL;
	spin_lock_init(&dlci->lock);
	mutex_init(&dlci->mutex);
	dlci->fifo = &dlci->_fifo;
	if (kfifo_alloc(&dlci->_fifo, 4096, GFP_KERNEL) < 0) {
		kfree(dlci);
		return NULL;
	}

	skb_queue_head_init(&dlci->skb_list);
	timer_setup(&dlci->t1, gsm_dlci_t1, 0);
	tty_port_init(&dlci->port);
	dlci->port.ops = &gsm_port_ops;
	dlci->gsm = gsm;
	dlci->addr = addr;
	dlci->adaption = gsm->adaption;
	dlci->state = DLCI_CLOSED;
	if (addr)
		dlci->data = gsm_dlci_data;
	else
		dlci->data = gsm_dlci_command;
	gsm->dlci[addr] = dlci;
	return dlci;
}