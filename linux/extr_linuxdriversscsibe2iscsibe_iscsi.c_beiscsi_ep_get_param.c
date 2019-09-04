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
struct iscsi_endpoint {struct beiscsi_endpoint* dd_data; } ;
struct beiscsi_endpoint {int /*<<< orphan*/  dst6_addr; int /*<<< orphan*/  dst_addr; int /*<<< orphan*/  ip_type; int /*<<< orphan*/ * dst_tcpport; int /*<<< orphan*/  phba; } ;
typedef  enum iscsi_param { ____Placeholder_iscsi_param } iscsi_param ;

/* Variables and functions */
 int /*<<< orphan*/  BEISCSI_IP_TYPE_V4 ; 
 int /*<<< orphan*/  BEISCSI_LOG_CONFIG ; 
 int EPERM ; 
#define  ISCSI_PARAM_CONN_ADDRESS 129 
#define  ISCSI_PARAM_CONN_PORT 128 
 int /*<<< orphan*/  KERN_INFO ; 
 int /*<<< orphan*/  beiscsi_log (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,int) ; 
 int sprintf (char*,char*,int /*<<< orphan*/ *) ; 

int beiscsi_ep_get_param(struct iscsi_endpoint *ep,
			   enum iscsi_param param, char *buf)
{
	struct beiscsi_endpoint *beiscsi_ep = ep->dd_data;
	int len;

	beiscsi_log(beiscsi_ep->phba, KERN_INFO,
		    BEISCSI_LOG_CONFIG,
		    "BS_%d : In beiscsi_ep_get_param,"
		    " param= %d\n", param);

	switch (param) {
	case ISCSI_PARAM_CONN_PORT:
		len = sprintf(buf, "%hu\n", beiscsi_ep->dst_tcpport);
		break;
	case ISCSI_PARAM_CONN_ADDRESS:
		if (beiscsi_ep->ip_type == BEISCSI_IP_TYPE_V4)
			len = sprintf(buf, "%pI4\n", &beiscsi_ep->dst_addr);
		else
			len = sprintf(buf, "%pI6\n", &beiscsi_ep->dst6_addr);
		break;
	default:
		len = -EPERM;
	}
	return len;
}