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
typedef  int /*<<< orphan*/  uint8_t ;
typedef  int /*<<< orphan*/  uint32_t ;
typedef  int /*<<< orphan*/  uint16_t ;
struct TYPE_2__ {int* s6_addr; } ;
struct in6_flowlabel_req {TYPE_1__ flr_dst; int /*<<< orphan*/  flr_share; int /*<<< orphan*/  flr_flags; int /*<<< orphan*/  flr_label; int /*<<< orphan*/  flr_action; } ;
typedef  int /*<<< orphan*/  req ;

/* Variables and functions */
 int /*<<< orphan*/  IPV6_FLOWLABEL_MGR ; 
 int /*<<< orphan*/  IPV6_FL_A_GET ; 
 int /*<<< orphan*/  SOL_IPV6 ; 
 int /*<<< orphan*/  htonl (int /*<<< orphan*/ ) ; 
 int setsockopt (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct in6_flowlabel_req*,int) ; 

__attribute__((used)) static int flowlabel_get(int fd, uint32_t label, uint8_t share, uint16_t flags)
{
	struct in6_flowlabel_req req = {
		.flr_action = IPV6_FL_A_GET,
		.flr_label = htonl(label),
		.flr_flags = flags,
		.flr_share = share,
	};

	/* do not pass IPV6_ADDR_ANY or IPV6_ADDR_MAPPED */
	req.flr_dst.s6_addr[0] = 0xfd;
	req.flr_dst.s6_addr[15] = 0x1;

	return setsockopt(fd, SOL_IPV6, IPV6_FLOWLABEL_MGR, &req, sizeof(req));
}