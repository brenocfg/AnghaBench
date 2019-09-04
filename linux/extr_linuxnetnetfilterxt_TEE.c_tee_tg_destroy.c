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
struct xt_tgdtor_param {struct xt_tee_tginfo* targinfo; int /*<<< orphan*/  net; } ;
struct xt_tee_tginfo {TYPE_1__* priv; } ;
struct tee_net {int /*<<< orphan*/  lock; } ;
struct TYPE_2__ {int /*<<< orphan*/  list; } ;

/* Variables and functions */
 int /*<<< orphan*/  kfree (TYPE_1__*) ; 
 int /*<<< orphan*/  list_del (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 struct tee_net* net_generic (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  static_key_slow_dec (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  tee_net_id ; 
 int /*<<< orphan*/  xt_tee_enabled ; 

__attribute__((used)) static void tee_tg_destroy(const struct xt_tgdtor_param *par)
{
	struct tee_net *tn = net_generic(par->net, tee_net_id);
	struct xt_tee_tginfo *info = par->targinfo;

	if (info->priv) {
		mutex_lock(&tn->lock);
		list_del(&info->priv->list);
		mutex_unlock(&tn->lock);
		kfree(info->priv);
	}
	static_key_slow_dec(&xt_tee_enabled);
}