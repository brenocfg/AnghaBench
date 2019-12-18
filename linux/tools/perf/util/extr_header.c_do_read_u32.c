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
typedef  int /*<<< orphan*/  u32 ;
struct feat_fd {TYPE_1__* ph; } ;
struct TYPE_2__ {scalar_t__ needs_swap; } ;

/* Variables and functions */
 int __do_read (struct feat_fd*,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  bswap_32 (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int do_read_u32(struct feat_fd *ff, u32 *addr)
{
	int ret;

	ret = __do_read(ff, addr, sizeof(*addr));
	if (ret)
		return ret;

	if (ff->ph->needs_swap)
		*addr = bswap_32(*addr);
	return 0;
}