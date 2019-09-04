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
struct fsg_config {int nluns; int /*<<< orphan*/ * luns; } ;
struct fsg_common {int dummy; } ;
typedef  int /*<<< orphan*/  buf ;

/* Variables and functions */
 int /*<<< orphan*/  _fsg_common_remove_luns (struct fsg_common*,int) ; 
 int fsg_common_create_lun (struct fsg_common*,int /*<<< orphan*/ *,int,char*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  fsg_common_remove_luns (struct fsg_common*) ; 
 int /*<<< orphan*/  pr_info (char*,int) ; 
 int /*<<< orphan*/  snprintf (char*,int,char*,int) ; 

int fsg_common_create_luns(struct fsg_common *common, struct fsg_config *cfg)
{
	char buf[8]; /* enough for 100000000 different numbers, decimal */
	int i, rc;

	fsg_common_remove_luns(common);

	for (i = 0; i < cfg->nluns; ++i) {
		snprintf(buf, sizeof(buf), "lun%d", i);
		rc = fsg_common_create_lun(common, &cfg->luns[i], i, buf, NULL);
		if (rc)
			goto fail;
	}

	pr_info("Number of LUNs=%d\n", cfg->nluns);

	return 0;

fail:
	_fsg_common_remove_luns(common, i);
	return rc;
}