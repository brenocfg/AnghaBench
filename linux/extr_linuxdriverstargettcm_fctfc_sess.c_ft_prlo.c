#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct ft_tport {int dummy; } ;
struct ft_sess {int dummy; } ;
struct TYPE_4__ {int /*<<< orphan*/  port_id; } ;
struct fc_rport_priv {int /*<<< orphan*/  prli_count; TYPE_2__ ids; TYPE_1__* local_port; } ;
struct TYPE_3__ {int /*<<< orphan*/ * prov; } ;

/* Variables and functions */
 size_t FC_TYPE_FCP ; 
 int /*<<< orphan*/  ft_close_sess (struct ft_sess*) ; 
 int /*<<< orphan*/  ft_lport_lock ; 
 struct ft_sess* ft_sess_delete (struct ft_tport*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lockdep_is_held (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 struct ft_tport* rcu_dereference_protected (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void ft_prlo(struct fc_rport_priv *rdata)
{
	struct ft_sess *sess;
	struct ft_tport *tport;

	mutex_lock(&ft_lport_lock);
	tport = rcu_dereference_protected(rdata->local_port->prov[FC_TYPE_FCP],
					  lockdep_is_held(&ft_lport_lock));

	if (!tport) {
		mutex_unlock(&ft_lport_lock);
		return;
	}
	sess = ft_sess_delete(tport, rdata->ids.port_id);
	if (!sess) {
		mutex_unlock(&ft_lport_lock);
		return;
	}
	mutex_unlock(&ft_lport_lock);
	ft_close_sess(sess);		/* release from table */
	rdata->prli_count--;
	/* XXX TBD - clearing actions.  unit attn, see 4.10 */
}