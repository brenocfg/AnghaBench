#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct block_device {int dummy; } ;
struct TYPE_5__ {int /*<<< orphan*/  j_devname; int /*<<< orphan*/  j_dev; } ;
typedef  TYPE_1__ journal_t ;

/* Variables and functions */
 int /*<<< orphan*/  bdevname (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  jbd2_stats_proc_init (TYPE_1__*) ; 
 TYPE_1__* journal_init_common (struct block_device*,struct block_device*,unsigned long long,int,int) ; 
 int /*<<< orphan*/  strreplace (int /*<<< orphan*/ ,char,char) ; 

journal_t *jbd2_journal_init_dev(struct block_device *bdev,
			struct block_device *fs_dev,
			unsigned long long start, int len, int blocksize)
{
	journal_t *journal;

	journal = journal_init_common(bdev, fs_dev, start, len, blocksize);
	if (!journal)
		return NULL;

	bdevname(journal->j_dev, journal->j_devname);
	strreplace(journal->j_devname, '/', '!');
	jbd2_stats_proc_init(journal);

	return journal;
}