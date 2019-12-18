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
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct sockaddr_in {int /*<<< orphan*/  sin_addr; } ;
struct sockaddr {int dummy; } ;
struct in_addr {int /*<<< orphan*/  s_addr; } ;
struct ip_mreq_source {struct in_addr imr_interface; int /*<<< orphan*/  imr_sourceaddr; int /*<<< orphan*/  imr_multiaddr; int /*<<< orphan*/  member_0; } ;
struct TYPE_6__ {scalar_t__ ss_family; } ;
struct group_source_req {unsigned int gsr_interface; TYPE_3__ gsr_source; TYPE_3__ gsr_group; int /*<<< orphan*/  member_0; } ;
typedef  int socklen_t ;
struct TYPE_5__ {scalar_t__ type; int /*<<< orphan*/  bsd_socket; } ;
typedef  TYPE_1__ php_socket ;
typedef  int /*<<< orphan*/  mreqs ;
typedef  int /*<<< orphan*/  gsreq ;
typedef  enum source_op { ____Placeholder_source_op } source_op ;

/* Variables and functions */
 scalar_t__ AF_INET ; 
 scalar_t__ AF_INET6 ; 
 int /*<<< orphan*/  E_WARNING ; 
 scalar_t__ FAILURE ; 
 int /*<<< orphan*/  INADDR_ANY ; 
 int /*<<< orphan*/  _php_source_op_to_ipv4_op (int) ; 
 int /*<<< orphan*/  _php_source_op_to_rfc3678_op (int) ; 
 int /*<<< orphan*/  _php_source_op_to_string (int) ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  htonl (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (TYPE_3__*,struct sockaddr*,int) ; 
 int /*<<< orphan*/  php_error_docref (int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 scalar_t__ php_if_index_to_addr4 (unsigned int,TYPE_1__*,struct in_addr*) ; 
 int setsockopt (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,char*,int) ; 

__attribute__((used)) static int _php_mcast_source_op(
	php_socket *sock,
	int level,
	struct sockaddr *group,
	socklen_t group_len,
	struct sockaddr *source,
	socklen_t source_len,
	unsigned int if_index,
	enum source_op sop)
{
#ifdef RFC3678_API
	struct group_source_req gsreq = {0};

	memcpy(&gsreq.gsr_group, group, group_len);
	assert(gsreq.gsr_group.ss_family != 0);
	memcpy(&gsreq.gsr_source, source, source_len);
	assert(gsreq.gsr_source.ss_family != 0);
	gsreq.gsr_interface = if_index;

	return setsockopt(sock->bsd_socket, level,
			_php_source_op_to_rfc3678_op(sop), (char*)&gsreq, sizeof(gsreq));
#else
	if (sock->type == AF_INET) {
		struct ip_mreq_source mreqs = {0};
		struct in_addr addr;

		mreqs.imr_multiaddr = ((struct sockaddr_in*)group)->sin_addr;
		mreqs.imr_sourceaddr =  ((struct sockaddr_in*)source)->sin_addr;

		assert(group_len == sizeof(struct sockaddr_in));
		assert(source_len == sizeof(struct sockaddr_in));

		if (if_index != 0) {
			if (php_if_index_to_addr4(if_index, sock, &addr) ==
					FAILURE)
				return -2; /* failure, but notice already emitted */
			mreqs.imr_interface = addr;
		} else {
			mreqs.imr_interface.s_addr = htonl(INADDR_ANY);
		}

		return setsockopt(sock->bsd_socket, level,
				_php_source_op_to_ipv4_op(sop), (char*)&mreqs, sizeof(mreqs));
	}
#if HAVE_IPV6
	else if (sock->type == AF_INET6) {
		php_error_docref(NULL, E_WARNING,
			"This platform does not support %s for IPv6 sockets",
			_php_source_op_to_string(sop));
		return -2;
	}
#endif
	else {
		php_error_docref(NULL, E_WARNING,
			"Option %s is inapplicable to this socket type",
			_php_source_op_to_string(sop));
		return -2;
	}
#endif
}