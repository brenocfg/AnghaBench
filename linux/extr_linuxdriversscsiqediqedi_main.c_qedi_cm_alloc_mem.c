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
typedef  int u16 ;
struct qedi_endpoint {int dummy; } ;
struct qedi_ctx {int max_active_conns; int /*<<< orphan*/  lcl_port_tbl; int /*<<< orphan*/  ep_tbl; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  QEDI_LOCAL_PORT_MIN ; 
 int QEDI_LOCAL_PORT_RANGE ; 
 int /*<<< orphan*/  kzalloc (int,int /*<<< orphan*/ ) ; 
 int prandom_u32 () ; 
 int /*<<< orphan*/  qedi_cm_free_mem (struct qedi_ctx*) ; 
 scalar_t__ qedi_init_id_tbl (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int qedi_cm_alloc_mem(struct qedi_ctx *qedi)
{
	u16 port_id;

	qedi->ep_tbl = kzalloc((qedi->max_active_conns *
				sizeof(struct qedi_endpoint *)), GFP_KERNEL);
	if (!qedi->ep_tbl)
		return -ENOMEM;
	port_id = prandom_u32() % QEDI_LOCAL_PORT_RANGE;
	if (qedi_init_id_tbl(&qedi->lcl_port_tbl, QEDI_LOCAL_PORT_RANGE,
			     QEDI_LOCAL_PORT_MIN, port_id)) {
		qedi_cm_free_mem(qedi);
		return -ENOMEM;
	}

	return 0;
}