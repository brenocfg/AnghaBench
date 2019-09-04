#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int /*<<< orphan*/  s_addr; } ;
struct TYPE_4__ {TYPE_1__ sin_addr; } ;
union sctp_addr {TYPE_2__ v4; } ;
typedef  enum sctp_scope { ____Placeholder_sctp_scope } sctp_scope ;

/* Variables and functions */
 scalar_t__ IS_IPV4_UNUSABLE_ADDRESS (int /*<<< orphan*/ ) ; 
 int SCTP_SCOPE_GLOBAL ; 
 int SCTP_SCOPE_LINK ; 
 int SCTP_SCOPE_LOOPBACK ; 
 int SCTP_SCOPE_PRIVATE ; 
 int SCTP_SCOPE_UNUSABLE ; 
 scalar_t__ ipv4_is_linklocal_169 (int /*<<< orphan*/ ) ; 
 scalar_t__ ipv4_is_loopback (int /*<<< orphan*/ ) ; 
 scalar_t__ ipv4_is_private_10 (int /*<<< orphan*/ ) ; 
 scalar_t__ ipv4_is_private_172 (int /*<<< orphan*/ ) ; 
 scalar_t__ ipv4_is_private_192 (int /*<<< orphan*/ ) ; 

__attribute__((used)) static enum sctp_scope sctp_v4_scope(union sctp_addr *addr)
{
	enum sctp_scope retval;

	/* Check for unusable SCTP addresses. */
	if (IS_IPV4_UNUSABLE_ADDRESS(addr->v4.sin_addr.s_addr)) {
		retval =  SCTP_SCOPE_UNUSABLE;
	} else if (ipv4_is_loopback(addr->v4.sin_addr.s_addr)) {
		retval = SCTP_SCOPE_LOOPBACK;
	} else if (ipv4_is_linklocal_169(addr->v4.sin_addr.s_addr)) {
		retval = SCTP_SCOPE_LINK;
	} else if (ipv4_is_private_10(addr->v4.sin_addr.s_addr) ||
		   ipv4_is_private_172(addr->v4.sin_addr.s_addr) ||
		   ipv4_is_private_192(addr->v4.sin_addr.s_addr)) {
		retval = SCTP_SCOPE_PRIVATE;
	} else {
		retval = SCTP_SCOPE_GLOBAL;
	}

	return retval;
}