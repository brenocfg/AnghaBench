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
struct snap {int /*<<< orphan*/  str; int /*<<< orphan*/  slen; } ;
struct mon_bus {int nreaders; int cnt_events; int cnt_text_lost; } ;
struct inode {struct mon_bus* i_private; } ;
struct file {struct snap* private_data; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  STAT_BUF_SIZE ; 
 struct snap* kmalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  snprintf (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,int,int,int) ; 

__attribute__((used)) static int mon_stat_open(struct inode *inode, struct file *file)
{
	struct mon_bus *mbus;
	struct snap *sp;

	sp = kmalloc(sizeof(struct snap), GFP_KERNEL);
	if (sp == NULL)
		return -ENOMEM;

	mbus = inode->i_private;

	sp->slen = snprintf(sp->str, STAT_BUF_SIZE,
	    "nreaders %d events %u text_lost %u\n",
	    mbus->nreaders, mbus->cnt_events, mbus->cnt_text_lost);

	file->private_data = sp;
	return 0;
}