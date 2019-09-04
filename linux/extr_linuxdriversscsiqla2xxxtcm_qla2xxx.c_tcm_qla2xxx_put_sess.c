#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct fc_port {int /*<<< orphan*/  sess_kref; TYPE_3__* vha; } ;
struct TYPE_6__ {TYPE_2__* hw; } ;
struct TYPE_4__ {int /*<<< orphan*/  sess_lock; } ;
struct TYPE_5__ {TYPE_1__ tgt; } ;

/* Variables and functions */
 int /*<<< orphan*/  assert_spin_locked (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  kref_put (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tcm_qla2xxx_release_session ; 

__attribute__((used)) static void tcm_qla2xxx_put_sess(struct fc_port *sess)
{
	if (!sess)
		return;

	assert_spin_locked(&sess->vha->hw->tgt.sess_lock);
	kref_put(&sess->sess_kref, tcm_qla2xxx_release_session);
}