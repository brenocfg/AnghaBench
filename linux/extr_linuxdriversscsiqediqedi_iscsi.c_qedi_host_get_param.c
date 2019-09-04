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
struct qedi_ctx {int src_ip; int /*<<< orphan*/  ip_type; int /*<<< orphan*/  mac; } ;
struct Scsi_Host {int host_no; } ;
typedef  enum iscsi_host_param { ____Placeholder_iscsi_host_param } iscsi_host_param ;

/* Variables and functions */
#define  ISCSI_HOST_PARAM_HWADDRESS 130 
#define  ISCSI_HOST_PARAM_IPADDRESS 129 
#define  ISCSI_HOST_PARAM_NETDEV_NAME 128 
 int /*<<< orphan*/  TCP_IPV4 ; 
 int iscsi_host_get_param (struct Scsi_Host*,int,char*) ; 
 struct qedi_ctx* iscsi_host_priv (struct Scsi_Host*) ; 
 int sprintf (char*,char*,int) ; 
 int sysfs_format_mac (char*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int qedi_host_get_param(struct Scsi_Host *shost,
			       enum iscsi_host_param param, char *buf)
{
	struct qedi_ctx *qedi;
	int len;

	qedi = iscsi_host_priv(shost);

	switch (param) {
	case ISCSI_HOST_PARAM_HWADDRESS:
		len = sysfs_format_mac(buf, qedi->mac, 6);
		break;
	case ISCSI_HOST_PARAM_NETDEV_NAME:
		len = sprintf(buf, "host%d\n", shost->host_no);
		break;
	case ISCSI_HOST_PARAM_IPADDRESS:
		if (qedi->ip_type == TCP_IPV4)
			len = sprintf(buf, "%pI4\n", qedi->src_ip);
		else
			len = sprintf(buf, "%pI6\n", qedi->src_ip);
		break;
	default:
		return iscsi_host_get_param(shost, param, buf);
	}

	return len;
}