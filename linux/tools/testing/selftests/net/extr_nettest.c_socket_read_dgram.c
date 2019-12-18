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
typedef  int /*<<< orphan*/  uint32_t ;
struct in6_addr {int /*<<< orphan*/  s6_addr; } ;
struct sockaddr_in6 {int sin6_scope_id; struct in6_addr sin6_addr; } ;
struct in_addr {int /*<<< orphan*/  s_addr; } ;
struct sockaddr_in {int /*<<< orphan*/  sin_family; struct in_addr sin_addr; } ;
struct sockaddr {scalar_t__ sa_family; } ;
struct sock_args {int expected_ifindex; scalar_t__ version; scalar_t__ dev; } ;
struct msghdr {void* msg_name; int msg_namelen; int msg_iovlen; int msg_controllen; void* msg_control; struct iovec* msg_iov; } ;
struct iovec {int iov_len; void* iov_base; } ;
struct cmsghdr {int dummy; } ;
typedef  int socklen_t ;
typedef  int /*<<< orphan*/  cmsgbuf ;
typedef  void* caddr_t ;
typedef  int /*<<< orphan*/  buf ;
typedef  int /*<<< orphan*/  addr ;

/* Variables and functions */
 int /*<<< orphan*/  AF_INET ; 
 scalar_t__ AF_INET6 ; 
 scalar_t__ EACCES ; 
 scalar_t__ IN6_IS_ADDR_V4MAPPED (struct in6_addr*) ; 
 scalar_t__ errno ; 
 int get_index_from_cmsg (struct msghdr*) ; 
 int /*<<< orphan*/  interactive ; 
 int /*<<< orphan*/  log_address (char*,struct sockaddr*) ; 
 int /*<<< orphan*/  log_err_errno (char*) ; 
 int /*<<< orphan*/  log_error (char*,int,int) ; 
 int /*<<< orphan*/  log_msg (char*,...) ; 
 int /*<<< orphan*/  memset (unsigned char*,int /*<<< orphan*/ ,int) ; 
 int recvmsg (int,struct msghdr*,int /*<<< orphan*/ ) ; 
 scalar_t__ send_msg_cmsg (int,unsigned char*,int,int,int /*<<< orphan*/ ) ; 
 int sendmsg (int,struct msghdr*,int /*<<< orphan*/ ) ; 
 scalar_t__ sendto (int,char*,int,int /*<<< orphan*/ ,void*,int) ; 
 scalar_t__ server_mode ; 
 int /*<<< orphan*/  set_broadcast (int) ; 
 char* strerror (scalar_t__) ; 
 scalar_t__ try_broadcast ; 

__attribute__((used)) static int socket_read_dgram(int sd, struct sock_args *args)
{
	unsigned char addr[sizeof(struct sockaddr_in6)];
	struct sockaddr *sa = (struct sockaddr *) addr;
	socklen_t alen = sizeof(addr);
	struct iovec iov[2];
	struct msghdr m = {
		.msg_name = (caddr_t)addr,
		.msg_namelen = alen,
		.msg_iov = iov,
		.msg_iovlen = 1,
	};
	unsigned char cmsgbuf[256];
	struct cmsghdr *cm = (struct cmsghdr *)cmsgbuf;
	char buf[16*1024];
	int ifindex;
	int len;

	iov[0].iov_base = (caddr_t)buf;
	iov[0].iov_len = sizeof(buf);

	memset(cmsgbuf, 0, sizeof(cmsgbuf));
	m.msg_control = (caddr_t)cm;
	m.msg_controllen = sizeof(cmsgbuf);

	len = recvmsg(sd, &m, 0);
	if (len == 0) {
		log_msg("peer closed connection.\n");
		return 0;
	} else if (len < 0) {
		log_msg("failed to read message: %d: %s\n",
			errno, strerror(errno));
		return -1;
	}

	buf[len] = '\0';

	log_address("Message from:", sa);
	log_msg("    %.24s%s\n", buf, len > 24 ? " ..." : "");

	ifindex = get_index_from_cmsg(&m);
	if (args->expected_ifindex) {
		if (args->expected_ifindex != ifindex) {
			log_error("Device index mismatch: expected %d have %d\n",
				  args->expected_ifindex, ifindex);
			return -1;
		}
		log_msg("Device index matches: expected %d have %d\n",
			args->expected_ifindex, ifindex);
	}

	if (!interactive && server_mode) {
		if (sa->sa_family == AF_INET6) {
			struct sockaddr_in6 *s6 = (struct sockaddr_in6 *) sa;
			struct in6_addr *in6 = &s6->sin6_addr;

			if (IN6_IS_ADDR_V4MAPPED(in6)) {
				const uint32_t *pa = (uint32_t *) &in6->s6_addr;
				struct in_addr in4;
				struct sockaddr_in *sin;

				sin = (struct sockaddr_in *) addr;
				pa += 3;
				in4.s_addr = *pa;
				sin->sin_addr = in4;
				sin->sin_family = AF_INET;
				if (send_msg_cmsg(sd, addr, alen,
						  ifindex, AF_INET) < 0)
					goto out_err;
			}
		}
again:
		iov[0].iov_len = len;

		if (args->version == AF_INET6) {
			struct sockaddr_in6 *s6 = (struct sockaddr_in6 *) sa;

			if (args->dev) {
				/* avoid PKTINFO conflicts with bindtodev */
				if (sendto(sd, buf, len, 0,
					   (void *) addr, alen) < 0)
					goto out_err;
			} else {
				/* kernel is allowing scope_id to be set to VRF
				 * index for LLA. for sends to global address
				 * reset scope id
				 */
				s6->sin6_scope_id = ifindex;
				if (sendmsg(sd, &m, 0) < 0)
					goto out_err;
			}
		} else {
			int err;

			err = sendmsg(sd, &m, 0);
			if (err < 0) {
				if (errno == EACCES && try_broadcast) {
					try_broadcast = 0;
					if (!set_broadcast(sd))
						goto again;
					errno = EACCES;
				}
				goto out_err;
			}
		}
		log_msg("Sent message:\n");
		log_msg("    %.24s%s\n", buf, len > 24 ? " ..." : "");
	}

	return 1;
out_err:
	log_err_errno("failed to send msg to peer");
	return -1;
}