#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_14__   TYPE_7__ ;
typedef  struct TYPE_13__   TYPE_6__ ;
typedef  struct TYPE_12__   TYPE_5__ ;
typedef  struct TYPE_11__   TYPE_4__ ;
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_9__ {scalar_t__ traffic_class; } ;
struct TYPE_8__ {scalar_t__ traffic_class; } ;
struct TYPE_10__ {scalar_t__ aal; TYPE_2__ txtp; TYPE_1__ rxtp; } ;
struct atm_vcc {TYPE_5__* dev; TYPE_3__ qos; } ;
struct TYPE_14__ {scalar_t__ traffic_class; } ;
struct atm_qos {scalar_t__ aal; TYPE_7__ rxtp; TYPE_7__ txtp; } ;
struct TYPE_13__ {scalar_t__ sk_family; } ;
struct TYPE_12__ {TYPE_4__* ops; } ;
struct TYPE_11__ {int (* change_qos ) (struct atm_vcc*,struct atm_qos*,int /*<<< orphan*/ ) ;} ;

/* Variables and functions */
 scalar_t__ AF_ATMPVC ; 
 int /*<<< orphan*/  ATM_MF_SET ; 
 int EINVAL ; 
 int EOPNOTSUPP ; 
 int adjust_tp (TYPE_7__*,scalar_t__) ; 
 TYPE_6__* sk_atm (struct atm_vcc*) ; 
 int stub1 (struct atm_vcc*,struct atm_qos*,int /*<<< orphan*/ ) ; 
 int svc_change_qos (struct atm_vcc*,struct atm_qos*) ; 

__attribute__((used)) static int atm_change_qos(struct atm_vcc *vcc, struct atm_qos *qos)
{
	int error;

	/*
	 * Don't let the QoS change the already connected AAL type nor the
	 * traffic class.
	 */
	if (qos->aal != vcc->qos.aal ||
	    qos->rxtp.traffic_class != vcc->qos.rxtp.traffic_class ||
	    qos->txtp.traffic_class != vcc->qos.txtp.traffic_class)
		return -EINVAL;
	error = adjust_tp(&qos->txtp, qos->aal);
	if (!error)
		error = adjust_tp(&qos->rxtp, qos->aal);
	if (error)
		return error;
	if (!vcc->dev->ops->change_qos)
		return -EOPNOTSUPP;
	if (sk_atm(vcc)->sk_family == AF_ATMPVC)
		return vcc->dev->ops->change_qos(vcc, qos, ATM_MF_SET);
	return svc_change_qos(vcc, qos);
}