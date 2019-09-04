#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int /*<<< orphan*/  a4; } ;
typedef  TYPE_1__ xfrm_address_t ;

/* Variables and functions */
 unsigned int ntohl (int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline unsigned int __xfrm4_addr_hash(const xfrm_address_t *addr)
{
	return ntohl(addr->a4);
}