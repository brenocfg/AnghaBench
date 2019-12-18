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
struct TYPE_2__ {int LeaseFlags; int /*<<< orphan*/  LeaseState; } ;
struct create_lease {TYPE_1__ lcontext; } ;
typedef  int /*<<< orphan*/  __u8 ;

/* Variables and functions */
 int SMB2_LEASE_FLAG_BREAK_IN_PROGRESS ; 
 int /*<<< orphan*/  SMB2_OPLOCK_LEVEL_NOCHANGE ; 
 int /*<<< orphan*/  le32_to_cpu (int /*<<< orphan*/ ) ; 

__attribute__((used)) static __u8
smb2_parse_lease_buf(void *buf, unsigned int *epoch, char *lease_key)
{
	struct create_lease *lc = (struct create_lease *)buf;

	*epoch = 0; /* not used */
	if (lc->lcontext.LeaseFlags & SMB2_LEASE_FLAG_BREAK_IN_PROGRESS)
		return SMB2_OPLOCK_LEVEL_NOCHANGE;
	return le32_to_cpu(lc->lcontext.LeaseState);
}