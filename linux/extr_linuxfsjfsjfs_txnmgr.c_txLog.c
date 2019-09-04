#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct tlock {int type; struct inode* ip; int /*<<< orphan*/  flag; scalar_t__ next; } ;
struct tblock {scalar_t__ next; } ;
struct TYPE_5__ {void* inode; void* fileset; } ;
struct TYPE_6__ {TYPE_1__ redopage; } ;
struct lrd {TYPE_2__ log; void* aggregate; } ;
struct jfs_log {int dummy; } ;
struct inode {int /*<<< orphan*/  i_ino; int /*<<< orphan*/  i_sb; } ;
struct commit {struct lrd lrd; } ;
typedef  scalar_t__ lid_t ;
struct TYPE_8__ {int /*<<< orphan*/  fileset; } ;
struct TYPE_7__ {int /*<<< orphan*/  aggregate; } ;

/* Variables and functions */
 TYPE_4__* JFS_IP (struct inode*) ; 
 TYPE_3__* JFS_SBI (int /*<<< orphan*/ ) ; 
 void* cpu_to_le32 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dataLog (struct jfs_log*,struct tblock*,struct lrd*,struct tlock*) ; 
 int /*<<< orphan*/  diLog (struct jfs_log*,struct tblock*,struct lrd*,struct tlock*,struct commit*) ; 
 int /*<<< orphan*/  dtLog (struct jfs_log*,struct tblock*,struct lrd*,struct tlock*) ; 
 int /*<<< orphan*/  jfs_err (char*,struct tlock*) ; 
 struct tlock* lid_to_tlock (scalar_t__) ; 
 int /*<<< orphan*/  mapLog (struct jfs_log*,struct tblock*,struct lrd*,struct tlock*) ; 
#define  tlckDATA 132 
#define  tlckDTREE 131 
#define  tlckINODE 130 
 int /*<<< orphan*/  tlckLOG ; 
#define  tlckMAP 129 
 int tlckTYPE ; 
#define  tlckXTREE 128 
 int /*<<< orphan*/  xtLog (struct jfs_log*,struct tblock*,struct lrd*,struct tlock*) ; 

__attribute__((used)) static int txLog(struct jfs_log * log, struct tblock * tblk, struct commit * cd)
{
	int rc = 0;
	struct inode *ip;
	lid_t lid;
	struct tlock *tlck;
	struct lrd *lrd = &cd->lrd;

	/*
	 * write log record(s) for each tlock of transaction,
	 */
	for (lid = tblk->next; lid; lid = tlck->next) {
		tlck = lid_to_tlock(lid);

		tlck->flag |= tlckLOG;

		/* initialize lrd common */
		ip = tlck->ip;
		lrd->aggregate = cpu_to_le32(JFS_SBI(ip->i_sb)->aggregate);
		lrd->log.redopage.fileset = cpu_to_le32(JFS_IP(ip)->fileset);
		lrd->log.redopage.inode = cpu_to_le32(ip->i_ino);

		/* write log record of page from the tlock */
		switch (tlck->type & tlckTYPE) {
		case tlckXTREE:
			xtLog(log, tblk, lrd, tlck);
			break;

		case tlckDTREE:
			dtLog(log, tblk, lrd, tlck);
			break;

		case tlckINODE:
			diLog(log, tblk, lrd, tlck, cd);
			break;

		case tlckMAP:
			mapLog(log, tblk, lrd, tlck);
			break;

		case tlckDATA:
			dataLog(log, tblk, lrd, tlck);
			break;

		default:
			jfs_err("UFO tlock:0x%p", tlck);
		}
	}

	return rc;
}