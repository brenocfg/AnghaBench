#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int lvl; int /*<<< orphan*/ * cat; } ;
struct TYPE_4__ {TYPE_1__ mls; } ;
struct netlbl_lsm_secattr {TYPE_2__ attr; int /*<<< orphan*/  flags; } ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_NOFS ; 
 int /*<<< orphan*/  NETLBL_SECATTR_MLS_CAT ; 
 int /*<<< orphan*/  netlbl_catmap_free (int /*<<< orphan*/ *) ; 
 int netlbl_catmap_setbit (int /*<<< orphan*/ **,int,int /*<<< orphan*/ ) ; 

int smk_netlbl_mls(int level, char *catset, struct netlbl_lsm_secattr *sap,
			int len)
{
	unsigned char *cp;
	unsigned char m;
	int cat;
	int rc;
	int byte;

	sap->flags |= NETLBL_SECATTR_MLS_CAT;
	sap->attr.mls.lvl = level;
	sap->attr.mls.cat = NULL;

	for (cat = 1, cp = catset, byte = 0; byte < len; cp++, byte++)
		for (m = 0x80; m != 0; m >>= 1, cat++) {
			if ((m & *cp) == 0)
				continue;
			rc = netlbl_catmap_setbit(&sap->attr.mls.cat,
						  cat, GFP_NOFS);
			if (rc < 0) {
				netlbl_catmap_free(sap->attr.mls.cat);
				return rc;
			}
		}

	return 0;
}