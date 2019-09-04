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
struct se_cmd {int /*<<< orphan*/  se_dev; } ;
typedef  int /*<<< orphan*/  sector_t ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  PAGE_SIZE ; 
 scalar_t__ __get_free_page (int /*<<< orphan*/ ) ; 
 int fd_do_prot_fill (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,void*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  free_page (unsigned long) ; 
 int /*<<< orphan*/  memset (void*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pr_err (char*) ; 

__attribute__((used)) static int
fd_do_prot_unmap(struct se_cmd *cmd, sector_t lba, sector_t nolb)
{
	void *buf;
	int rc;

	buf = (void *)__get_free_page(GFP_KERNEL);
	if (!buf) {
		pr_err("Unable to allocate FILEIO prot buf\n");
		return -ENOMEM;
	}
	memset(buf, 0xff, PAGE_SIZE);

	rc = fd_do_prot_fill(cmd->se_dev, lba, nolb, buf, PAGE_SIZE);

	free_page((unsigned long)buf);

	return rc;
}