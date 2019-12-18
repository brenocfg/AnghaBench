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
struct sock {int dummy; } ;

/* Variables and functions */
 scalar_t__ nla_total_size (int) ; 

__attribute__((used)) static size_t tls_get_info_size(const struct sock *sk)
{
	size_t size = 0;

	size += nla_total_size(0) +		/* INET_ULP_INFO_TLS */
		nla_total_size(sizeof(u16)) +	/* TLS_INFO_VERSION */
		nla_total_size(sizeof(u16)) +	/* TLS_INFO_CIPHER */
		nla_total_size(sizeof(u16)) +	/* TLS_INFO_RXCONF */
		nla_total_size(sizeof(u16)) +	/* TLS_INFO_TXCONF */
		0;

	return size;
}