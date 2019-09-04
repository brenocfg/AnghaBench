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
struct attribute_container {int /*<<< orphan*/ * class; } ;
struct TYPE_4__ {struct attribute_container ac; } ;
struct iscsi_internal {TYPE_1__ conn_cont; } ;
struct iscsi_cls_session {int dummy; } ;
struct TYPE_5__ {int /*<<< orphan*/  parent; } ;
struct iscsi_cls_conn {TYPE_2__ dev; } ;
struct device {int dummy; } ;
struct Scsi_Host {int /*<<< orphan*/  transportt; } ;
struct TYPE_6__ {int /*<<< orphan*/  class; } ;

/* Variables and functions */
 TYPE_3__ iscsi_connection_class ; 
 struct iscsi_cls_conn* iscsi_dev_to_conn (struct device*) ; 
 struct iscsi_cls_session* iscsi_dev_to_session (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  iscsi_is_conn_dev (struct device*) ; 
 struct Scsi_Host* iscsi_session_to_shost (struct iscsi_cls_session*) ; 
 struct iscsi_internal* to_iscsi_internal (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int iscsi_conn_match(struct attribute_container *cont,
			   struct device *dev)
{
	struct iscsi_cls_session *session;
	struct iscsi_cls_conn *conn;
	struct Scsi_Host *shost;
	struct iscsi_internal *priv;

	if (!iscsi_is_conn_dev(dev))
		return 0;

	conn = iscsi_dev_to_conn(dev);
	session = iscsi_dev_to_session(conn->dev.parent);
	shost = iscsi_session_to_shost(session);

	if (!shost->transportt)
		return 0;

	priv = to_iscsi_internal(shost->transportt);
	if (priv->conn_cont.ac.class != &iscsi_connection_class.class)
		return 0;

	return &priv->conn_cont.ac == cont;
}