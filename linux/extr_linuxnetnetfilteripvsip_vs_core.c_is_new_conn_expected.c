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
struct ip_vs_conn {int protocol; int flags; int /*<<< orphan*/  state; scalar_t__ control; } ;

/* Variables and functions */
#define  IPPROTO_SCTP 129 
#define  IPPROTO_TCP 128 
 int IP_VS_CONN_F_NOOUTPUT ; 
 int /*<<< orphan*/  IP_VS_SCTP_S_CLOSED ; 
 int /*<<< orphan*/  IP_VS_TCP_S_CLOSE ; 
 int /*<<< orphan*/  IP_VS_TCP_S_FIN_WAIT ; 
 int /*<<< orphan*/  IP_VS_TCP_S_TIME_WAIT ; 

__attribute__((used)) static inline bool is_new_conn_expected(const struct ip_vs_conn *cp,
					int conn_reuse_mode)
{
	/* Controlled (FTP DATA or persistence)? */
	if (cp->control)
		return false;

	switch (cp->protocol) {
	case IPPROTO_TCP:
		return (cp->state == IP_VS_TCP_S_TIME_WAIT) ||
		       (cp->state == IP_VS_TCP_S_CLOSE) ||
			((conn_reuse_mode & 2) &&
			 (cp->state == IP_VS_TCP_S_FIN_WAIT) &&
			 (cp->flags & IP_VS_CONN_F_NOOUTPUT));
	case IPPROTO_SCTP:
		return cp->state == IP_VS_SCTP_S_CLOSED;
	default:
		return false;
	}
}