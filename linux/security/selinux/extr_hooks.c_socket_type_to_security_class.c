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
typedef  int /*<<< orphan*/  u16 ;

/* Variables and functions */
 int IPPROTO_ICMP ; 
 int IPPROTO_ICMPV6 ; 
 int IPPROTO_SCTP ; 
#define  NETLINK_AUDIT 183 
#define  NETLINK_CONNECTOR 182 
#define  NETLINK_CRYPTO 181 
#define  NETLINK_DNRTMSG 180 
#define  NETLINK_FIB_LOOKUP 179 
#define  NETLINK_GENERIC 178 
#define  NETLINK_ISCSI 177 
#define  NETLINK_KOBJECT_UEVENT 176 
#define  NETLINK_NETFILTER 175 
#define  NETLINK_NFLOG 174 
#define  NETLINK_RDMA 173 
#define  NETLINK_ROUTE 172 
#define  NETLINK_SCSITRANSPORT 171 
#define  NETLINK_SELINUX 170 
#define  NETLINK_SOCK_DIAG 169 
#define  NETLINK_XFRM 168 
#define  PF_ALG 167 
#define  PF_APPLETALK 166 
#define  PF_ATMPVC 165 
#define  PF_ATMSVC 164 
#define  PF_AX25 163 
#define  PF_BLUETOOTH 162 
#define  PF_CAIF 161 
#define  PF_CAN 160 
#define  PF_DECnet 159 
#define  PF_IEEE802154 158 
#define  PF_INET 157 
#define  PF_INET6 156 
#define  PF_IPX 155 
#define  PF_IRDA 154 
#define  PF_ISDN 153 
#define  PF_IUCV 152 
#define  PF_KCM 151 
#define  PF_KEY 150 
#define  PF_LLC 149 
#define  PF_NETLINK 148 
#define  PF_NETROM 147 
#define  PF_NFC 146 
#define  PF_PACKET 145 
#define  PF_PHONET 144 
#define  PF_PPPOX 143 
#define  PF_QIPCRTR 142 
#define  PF_RDS 141 
#define  PF_ROSE 140 
#define  PF_RXRPC 139 
#define  PF_SMC 138 
#define  PF_TIPC 137 
#define  PF_UNIX 136 
#define  PF_VSOCK 135 
#define  PF_X25 134 
#define  PF_XDP 133 
 int /*<<< orphan*/  SECCLASS_ALG_SOCKET ; 
 int /*<<< orphan*/  SECCLASS_APPLETALK_SOCKET ; 
 int /*<<< orphan*/  SECCLASS_ATMPVC_SOCKET ; 
 int /*<<< orphan*/  SECCLASS_ATMSVC_SOCKET ; 
 int /*<<< orphan*/  SECCLASS_AX25_SOCKET ; 
 int /*<<< orphan*/  SECCLASS_BLUETOOTH_SOCKET ; 
 int /*<<< orphan*/  SECCLASS_CAIF_SOCKET ; 
 int /*<<< orphan*/  SECCLASS_CAN_SOCKET ; 
 int /*<<< orphan*/  SECCLASS_DCCP_SOCKET ; 
 int /*<<< orphan*/  SECCLASS_DECNET_SOCKET ; 
 int /*<<< orphan*/  SECCLASS_ICMP_SOCKET ; 
 int /*<<< orphan*/  SECCLASS_IEEE802154_SOCKET ; 
 int /*<<< orphan*/  SECCLASS_IPX_SOCKET ; 
 int /*<<< orphan*/  SECCLASS_IRDA_SOCKET ; 
 int /*<<< orphan*/  SECCLASS_ISDN_SOCKET ; 
 int /*<<< orphan*/  SECCLASS_IUCV_SOCKET ; 
 int /*<<< orphan*/  SECCLASS_KCM_SOCKET ; 
 int /*<<< orphan*/  SECCLASS_KEY_SOCKET ; 
 int /*<<< orphan*/  SECCLASS_LLC_SOCKET ; 
 int /*<<< orphan*/  SECCLASS_NETLINK_AUDIT_SOCKET ; 
 int /*<<< orphan*/  SECCLASS_NETLINK_CONNECTOR_SOCKET ; 
 int /*<<< orphan*/  SECCLASS_NETLINK_CRYPTO_SOCKET ; 
 int /*<<< orphan*/  SECCLASS_NETLINK_DNRT_SOCKET ; 
 int /*<<< orphan*/  SECCLASS_NETLINK_FIB_LOOKUP_SOCKET ; 
 int /*<<< orphan*/  SECCLASS_NETLINK_GENERIC_SOCKET ; 
 int /*<<< orphan*/  SECCLASS_NETLINK_ISCSI_SOCKET ; 
 int /*<<< orphan*/  SECCLASS_NETLINK_KOBJECT_UEVENT_SOCKET ; 
 int /*<<< orphan*/  SECCLASS_NETLINK_NETFILTER_SOCKET ; 
 int /*<<< orphan*/  SECCLASS_NETLINK_NFLOG_SOCKET ; 
 int /*<<< orphan*/  SECCLASS_NETLINK_RDMA_SOCKET ; 
 int /*<<< orphan*/  SECCLASS_NETLINK_ROUTE_SOCKET ; 
 int /*<<< orphan*/  SECCLASS_NETLINK_SCSITRANSPORT_SOCKET ; 
 int /*<<< orphan*/  SECCLASS_NETLINK_SELINUX_SOCKET ; 
 int /*<<< orphan*/  SECCLASS_NETLINK_SOCKET ; 
 int /*<<< orphan*/  SECCLASS_NETLINK_TCPDIAG_SOCKET ; 
 int /*<<< orphan*/  SECCLASS_NETLINK_XFRM_SOCKET ; 
 int /*<<< orphan*/  SECCLASS_NETROM_SOCKET ; 
 int /*<<< orphan*/  SECCLASS_NFC_SOCKET ; 
 int /*<<< orphan*/  SECCLASS_PACKET_SOCKET ; 
 int /*<<< orphan*/  SECCLASS_PHONET_SOCKET ; 
 int /*<<< orphan*/  SECCLASS_PPPOX_SOCKET ; 
 int /*<<< orphan*/  SECCLASS_QIPCRTR_SOCKET ; 
 int /*<<< orphan*/  SECCLASS_RAWIP_SOCKET ; 
 int /*<<< orphan*/  SECCLASS_RDS_SOCKET ; 
 int /*<<< orphan*/  SECCLASS_ROSE_SOCKET ; 
 int /*<<< orphan*/  SECCLASS_RXRPC_SOCKET ; 
 int /*<<< orphan*/  SECCLASS_SCTP_SOCKET ; 
 int /*<<< orphan*/  SECCLASS_SMC_SOCKET ; 
 int /*<<< orphan*/  SECCLASS_SOCKET ; 
 int /*<<< orphan*/  SECCLASS_TCP_SOCKET ; 
 int /*<<< orphan*/  SECCLASS_TIPC_SOCKET ; 
 int /*<<< orphan*/  SECCLASS_UDP_SOCKET ; 
 int /*<<< orphan*/  SECCLASS_UNIX_DGRAM_SOCKET ; 
 int /*<<< orphan*/  SECCLASS_UNIX_STREAM_SOCKET ; 
 int /*<<< orphan*/  SECCLASS_VSOCK_SOCKET ; 
 int /*<<< orphan*/  SECCLASS_X25_SOCKET ; 
 int /*<<< orphan*/  SECCLASS_XDP_SOCKET ; 
#define  SOCK_DCCP 132 
#define  SOCK_DGRAM 131 
#define  SOCK_RAW 130 
#define  SOCK_SEQPACKET 129 
#define  SOCK_STREAM 128 
 int /*<<< orphan*/  default_protocol_dgram (int) ; 
 int /*<<< orphan*/  default_protocol_stream (int) ; 
 int selinux_policycap_extsockclass () ; 

__attribute__((used)) static inline u16 socket_type_to_security_class(int family, int type, int protocol)
{
	int extsockclass = selinux_policycap_extsockclass();

	switch (family) {
	case PF_UNIX:
		switch (type) {
		case SOCK_STREAM:
		case SOCK_SEQPACKET:
			return SECCLASS_UNIX_STREAM_SOCKET;
		case SOCK_DGRAM:
		case SOCK_RAW:
			return SECCLASS_UNIX_DGRAM_SOCKET;
		}
		break;
	case PF_INET:
	case PF_INET6:
		switch (type) {
		case SOCK_STREAM:
		case SOCK_SEQPACKET:
			if (default_protocol_stream(protocol))
				return SECCLASS_TCP_SOCKET;
			else if (extsockclass && protocol == IPPROTO_SCTP)
				return SECCLASS_SCTP_SOCKET;
			else
				return SECCLASS_RAWIP_SOCKET;
		case SOCK_DGRAM:
			if (default_protocol_dgram(protocol))
				return SECCLASS_UDP_SOCKET;
			else if (extsockclass && (protocol == IPPROTO_ICMP ||
						  protocol == IPPROTO_ICMPV6))
				return SECCLASS_ICMP_SOCKET;
			else
				return SECCLASS_RAWIP_SOCKET;
		case SOCK_DCCP:
			return SECCLASS_DCCP_SOCKET;
		default:
			return SECCLASS_RAWIP_SOCKET;
		}
		break;
	case PF_NETLINK:
		switch (protocol) {
		case NETLINK_ROUTE:
			return SECCLASS_NETLINK_ROUTE_SOCKET;
		case NETLINK_SOCK_DIAG:
			return SECCLASS_NETLINK_TCPDIAG_SOCKET;
		case NETLINK_NFLOG:
			return SECCLASS_NETLINK_NFLOG_SOCKET;
		case NETLINK_XFRM:
			return SECCLASS_NETLINK_XFRM_SOCKET;
		case NETLINK_SELINUX:
			return SECCLASS_NETLINK_SELINUX_SOCKET;
		case NETLINK_ISCSI:
			return SECCLASS_NETLINK_ISCSI_SOCKET;
		case NETLINK_AUDIT:
			return SECCLASS_NETLINK_AUDIT_SOCKET;
		case NETLINK_FIB_LOOKUP:
			return SECCLASS_NETLINK_FIB_LOOKUP_SOCKET;
		case NETLINK_CONNECTOR:
			return SECCLASS_NETLINK_CONNECTOR_SOCKET;
		case NETLINK_NETFILTER:
			return SECCLASS_NETLINK_NETFILTER_SOCKET;
		case NETLINK_DNRTMSG:
			return SECCLASS_NETLINK_DNRT_SOCKET;
		case NETLINK_KOBJECT_UEVENT:
			return SECCLASS_NETLINK_KOBJECT_UEVENT_SOCKET;
		case NETLINK_GENERIC:
			return SECCLASS_NETLINK_GENERIC_SOCKET;
		case NETLINK_SCSITRANSPORT:
			return SECCLASS_NETLINK_SCSITRANSPORT_SOCKET;
		case NETLINK_RDMA:
			return SECCLASS_NETLINK_RDMA_SOCKET;
		case NETLINK_CRYPTO:
			return SECCLASS_NETLINK_CRYPTO_SOCKET;
		default:
			return SECCLASS_NETLINK_SOCKET;
		}
	case PF_PACKET:
		return SECCLASS_PACKET_SOCKET;
	case PF_KEY:
		return SECCLASS_KEY_SOCKET;
	case PF_APPLETALK:
		return SECCLASS_APPLETALK_SOCKET;
	}

	if (extsockclass) {
		switch (family) {
		case PF_AX25:
			return SECCLASS_AX25_SOCKET;
		case PF_IPX:
			return SECCLASS_IPX_SOCKET;
		case PF_NETROM:
			return SECCLASS_NETROM_SOCKET;
		case PF_ATMPVC:
			return SECCLASS_ATMPVC_SOCKET;
		case PF_X25:
			return SECCLASS_X25_SOCKET;
		case PF_ROSE:
			return SECCLASS_ROSE_SOCKET;
		case PF_DECnet:
			return SECCLASS_DECNET_SOCKET;
		case PF_ATMSVC:
			return SECCLASS_ATMSVC_SOCKET;
		case PF_RDS:
			return SECCLASS_RDS_SOCKET;
		case PF_IRDA:
			return SECCLASS_IRDA_SOCKET;
		case PF_PPPOX:
			return SECCLASS_PPPOX_SOCKET;
		case PF_LLC:
			return SECCLASS_LLC_SOCKET;
		case PF_CAN:
			return SECCLASS_CAN_SOCKET;
		case PF_TIPC:
			return SECCLASS_TIPC_SOCKET;
		case PF_BLUETOOTH:
			return SECCLASS_BLUETOOTH_SOCKET;
		case PF_IUCV:
			return SECCLASS_IUCV_SOCKET;
		case PF_RXRPC:
			return SECCLASS_RXRPC_SOCKET;
		case PF_ISDN:
			return SECCLASS_ISDN_SOCKET;
		case PF_PHONET:
			return SECCLASS_PHONET_SOCKET;
		case PF_IEEE802154:
			return SECCLASS_IEEE802154_SOCKET;
		case PF_CAIF:
			return SECCLASS_CAIF_SOCKET;
		case PF_ALG:
			return SECCLASS_ALG_SOCKET;
		case PF_NFC:
			return SECCLASS_NFC_SOCKET;
		case PF_VSOCK:
			return SECCLASS_VSOCK_SOCKET;
		case PF_KCM:
			return SECCLASS_KCM_SOCKET;
		case PF_QIPCRTR:
			return SECCLASS_QIPCRTR_SOCKET;
		case PF_SMC:
			return SECCLASS_SMC_SOCKET;
		case PF_XDP:
			return SECCLASS_XDP_SOCKET;
#if PF_MAX > 45
#error New address family defined, please update this function.
#endif
		}
	}

	return SECCLASS_SOCKET;
}