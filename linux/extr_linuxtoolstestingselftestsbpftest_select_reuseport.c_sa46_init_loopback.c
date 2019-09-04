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
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int /*<<< orphan*/  s_addr; } ;
struct TYPE_6__ {TYPE_2__ sin_addr; } ;
struct TYPE_4__ {int /*<<< orphan*/  sin6_addr; } ;
union sa46 {scalar_t__ family; TYPE_3__ v4; TYPE_1__ v6; } ;
typedef  scalar_t__ sa_family_t ;

/* Variables and functions */
 scalar_t__ AF_INET6 ; 
 int /*<<< orphan*/  INADDR_LOOPBACK ; 
 int /*<<< orphan*/  htonl (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  in6addr_loopback ; 
 int /*<<< orphan*/  memset (union sa46*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void sa46_init_loopback(union sa46 *sa, sa_family_t family)
{
	memset(sa, 0, sizeof(*sa));
	sa->family = family;
	if (sa->family == AF_INET6)
		sa->v6.sin6_addr = in6addr_loopback;
	else
		sa->v4.sin_addr.s_addr = htonl(INADDR_LOOPBACK);
}