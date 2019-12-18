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
struct in6_flowlabel_req {int /*<<< orphan*/  flr_label; int /*<<< orphan*/  flr_action; } ;
typedef  int /*<<< orphan*/  req ;

/* Variables and functions */
 int /*<<< orphan*/  IPV6_FLOWLABEL_MGR ; 
 int /*<<< orphan*/  IPV6_FL_A_PUT ; 
 int /*<<< orphan*/  SOL_IPV6 ; 
 int /*<<< orphan*/  htonl (int /*<<< orphan*/ ) ; 
 int setsockopt (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct in6_flowlabel_req*,int) ; 

__attribute__((used)) static int flowlabel_put(int fd, uint32_t label)
{
	struct in6_flowlabel_req req = {
		.flr_action = IPV6_FL_A_PUT,
		.flr_label = htonl(label),
	};

	return setsockopt(fd, SOL_IPV6, IPV6_FLOWLABEL_MGR, &req, sizeof(req));
}