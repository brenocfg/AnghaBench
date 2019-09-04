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
struct gsm_mux {int adaption; int encoding; int mru; int mtu; int dead; int /*<<< orphan*/  ftype; int /*<<< orphan*/  n2; int /*<<< orphan*/  t2; int /*<<< orphan*/  t1; int /*<<< orphan*/  tx_list; int /*<<< orphan*/  ref; int /*<<< orphan*/  mutex; int /*<<< orphan*/  lock; struct gsm_mux* buf; int /*<<< orphan*/ * txframe; } ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  INIT_LIST_HEAD (int /*<<< orphan*/ *) ; 
 int MAX_MRU ; 
 int /*<<< orphan*/  N2 ; 
 int /*<<< orphan*/  T1 ; 
 int /*<<< orphan*/  T2 ; 
 int /*<<< orphan*/  UIH ; 
 int /*<<< orphan*/  kfree (struct gsm_mux*) ; 
 void* kmalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kref_init (int /*<<< orphan*/ *) ; 
 struct gsm_mux* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mutex_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock_init (int /*<<< orphan*/ *) ; 

__attribute__((used)) static struct gsm_mux *gsm_alloc_mux(void)
{
	struct gsm_mux *gsm = kzalloc(sizeof(struct gsm_mux), GFP_KERNEL);
	if (gsm == NULL)
		return NULL;
	gsm->buf = kmalloc(MAX_MRU + 1, GFP_KERNEL);
	if (gsm->buf == NULL) {
		kfree(gsm);
		return NULL;
	}
	gsm->txframe = kmalloc(2 * MAX_MRU + 2, GFP_KERNEL);
	if (gsm->txframe == NULL) {
		kfree(gsm->buf);
		kfree(gsm);
		return NULL;
	}
	spin_lock_init(&gsm->lock);
	mutex_init(&gsm->mutex);
	kref_init(&gsm->ref);
	INIT_LIST_HEAD(&gsm->tx_list);

	gsm->t1 = T1;
	gsm->t2 = T2;
	gsm->n2 = N2;
	gsm->ftype = UIH;
	gsm->adaption = 1;
	gsm->encoding = 1;
	gsm->mru = 64;	/* Default to encoding 1 so these should be 64 */
	gsm->mtu = 64;
	gsm->dead = 1;	/* Avoid early tty opens */

	return gsm;
}