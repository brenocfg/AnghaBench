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
struct file {int dummy; } ;
typedef  int /*<<< orphan*/  loff_t ;

/* Variables and functions */
 int /*<<< orphan*/  FYI ; 
 int /*<<< orphan*/  cifs_dbg (int /*<<< orphan*/ ,char*,struct file*,int) ; 

__attribute__((used)) static int cifs_dir_fsync(struct file *file, loff_t start, loff_t end, int datasync)
{
	cifs_dbg(FYI, "Sync directory - name: %pD datasync: 0x%x\n",
		 file, datasync);

	return 0;
}