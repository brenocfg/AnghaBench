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
struct tb {TYPE_1__* cm_ops; } ;
typedef  enum tb_cfg_pkg_type { ____Placeholder_tb_cfg_pkg_type } tb_cfg_pkg_type ;
struct TYPE_2__ {int /*<<< orphan*/  (* handle_event ) (struct tb*,int,void const*,size_t) ;} ;

/* Variables and functions */
#define  TB_CFG_PKG_XDOMAIN_REQ 129 
#define  TB_CFG_PKG_XDOMAIN_RESP 128 
 int /*<<< orphan*/  stub1 (struct tb*,int,void const*,size_t) ; 
 int /*<<< orphan*/  tb_warn (struct tb*,char*) ; 
 int tb_xdomain_handle_request (struct tb*,int,void const*,size_t) ; 

__attribute__((used)) static bool tb_domain_event_cb(void *data, enum tb_cfg_pkg_type type,
			       const void *buf, size_t size)
{
	struct tb *tb = data;

	if (!tb->cm_ops->handle_event) {
		tb_warn(tb, "domain does not have event handler\n");
		return true;
	}

	switch (type) {
	case TB_CFG_PKG_XDOMAIN_REQ:
	case TB_CFG_PKG_XDOMAIN_RESP:
		return tb_xdomain_handle_request(tb, type, buf, size);

	default:
		tb->cm_ops->handle_event(tb, type, buf, size);
	}

	return true;
}