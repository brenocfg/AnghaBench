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
struct v2_disk_dqheader {int dummy; } ;
struct super_block {TYPE_1__* s_op; } ;
typedef  int ssize_t ;
struct TYPE_2__ {int (* quota_read ) (struct super_block*,int,char*,int,int /*<<< orphan*/ ) ;} ;

/* Variables and functions */
 int EIO ; 
 int /*<<< orphan*/  quota_error (struct super_block*,char*,int,int) ; 
 int stub1 (struct super_block*,int,char*,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int v2_read_header(struct super_block *sb, int type,
			  struct v2_disk_dqheader *dqhead)
{
	ssize_t size;

	size = sb->s_op->quota_read(sb, type, (char *)dqhead,
				    sizeof(struct v2_disk_dqheader), 0);
	if (size != sizeof(struct v2_disk_dqheader)) {
		quota_error(sb, "Failed header read: expected=%zd got=%zd",
			    sizeof(struct v2_disk_dqheader), size);
		if (size < 0)
			return size;
		return -EIO;
	}
	return 0;
}