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
struct TYPE_2__ {int /*<<< orphan*/  s_addr; } ;
struct sockaddr_in {TYPE_1__ sin_addr; } ;
struct sockaddr {int dummy; } ;

/* Variables and functions */
 unsigned int __nlm_hash32 (int /*<<< orphan*/ ) ; 

__attribute__((used)) static unsigned int __nlm_hash_addr4(const struct sockaddr *sap)
{
	const struct sockaddr_in *sin = (struct sockaddr_in *)sap;
	return __nlm_hash32(sin->sin_addr.s_addr);
}