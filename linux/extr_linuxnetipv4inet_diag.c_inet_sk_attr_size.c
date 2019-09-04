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
struct tcpvegas_info {int dummy; } ;
struct tcp_info {int dummy; } ;
struct sock {int dummy; } ;
struct inet_diag_req_v2 {size_t sdiag_protocol; } ;
struct inet_diag_msg {int dummy; } ;
struct inet_diag_meminfo {int dummy; } ;
struct inet_diag_handler {size_t (* idiag_get_aux_size ) (struct sock*,int) ;} ;

/* Variables and functions */
 int SK_MEMINFO_VARS ; 
 int TCP_CA_NAME_MAX ; 
 struct inet_diag_handler** inet_diag_table ; 
 size_t nla_total_size (int) ; 
 size_t stub1 (struct sock*,int) ; 

__attribute__((used)) static size_t inet_sk_attr_size(struct sock *sk,
				const struct inet_diag_req_v2 *req,
				bool net_admin)
{
	const struct inet_diag_handler *handler;
	size_t aux = 0;

	handler = inet_diag_table[req->sdiag_protocol];
	if (handler && handler->idiag_get_aux_size)
		aux = handler->idiag_get_aux_size(sk, net_admin);

	return	  nla_total_size(sizeof(struct tcp_info))
		+ nla_total_size(1) /* INET_DIAG_SHUTDOWN */
		+ nla_total_size(1) /* INET_DIAG_TOS */
		+ nla_total_size(1) /* INET_DIAG_TCLASS */
		+ nla_total_size(4) /* INET_DIAG_MARK */
		+ nla_total_size(4) /* INET_DIAG_CLASS_ID */
		+ nla_total_size(sizeof(struct inet_diag_meminfo))
		+ nla_total_size(sizeof(struct inet_diag_msg))
		+ nla_total_size(SK_MEMINFO_VARS * sizeof(u32))
		+ nla_total_size(TCP_CA_NAME_MAX)
		+ nla_total_size(sizeof(struct tcpvegas_info))
		+ aux
		+ 64;
}