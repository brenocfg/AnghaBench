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
struct TYPE_4__ {int* magic; int /*<<< orphan*/  skip; } ;
struct TYPE_5__ {TYPE_1__ SP; } ;
struct rock_ridge {TYPE_2__ u; } ;
struct inode {int /*<<< orphan*/  i_sb; } ;
struct TYPE_6__ {int /*<<< orphan*/  s_rock_offset; } ;

/* Variables and functions */
 TYPE_3__* ISOFS_SB (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int check_sp(struct rock_ridge *rr, struct inode *inode)
{
	if (rr->u.SP.magic[0] != 0xbe)
		return -1;
	if (rr->u.SP.magic[1] != 0xef)
		return -1;
	ISOFS_SB(inode->i_sb)->s_rock_offset = rr->u.SP.skip;
	return 0;
}