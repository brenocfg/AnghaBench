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
typedef  int /*<<< orphan*/  u32 ;
struct zfcp_fc_wka_port {int /*<<< orphan*/  work; int /*<<< orphan*/  mutex; int /*<<< orphan*/  refcount; int /*<<< orphan*/  status; int /*<<< orphan*/  d_id; struct zfcp_adapter* adapter; int /*<<< orphan*/  completion_wq; } ;
struct zfcp_adapter {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  INIT_DELAYED_WORK (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ZFCP_FC_WKA_PORT_OFFLINE ; 
 int /*<<< orphan*/  atomic_set (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  init_waitqueue_head (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  zfcp_fc_wka_port_offline ; 

__attribute__((used)) static void zfcp_fc_wka_port_init(struct zfcp_fc_wka_port *wka_port, u32 d_id,
				  struct zfcp_adapter *adapter)
{
	init_waitqueue_head(&wka_port->completion_wq);

	wka_port->adapter = adapter;
	wka_port->d_id = d_id;

	wka_port->status = ZFCP_FC_WKA_PORT_OFFLINE;
	atomic_set(&wka_port->refcount, 0);
	mutex_init(&wka_port->mutex);
	INIT_DELAYED_WORK(&wka_port->work, zfcp_fc_wka_port_offline);
}