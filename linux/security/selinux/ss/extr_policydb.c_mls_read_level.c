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
struct mls_level {int /*<<< orphan*/  cat; int /*<<< orphan*/  sens; } ;
typedef  int /*<<< orphan*/  __le32 ;

/* Variables and functions */
 int ebitmap_read (int /*<<< orphan*/ *,void*) ; 
 int /*<<< orphan*/  le32_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memset (struct mls_level*,int /*<<< orphan*/ ,int) ; 
 int next_entry (int /*<<< orphan*/ *,void*,int) ; 
 int /*<<< orphan*/  pr_err (char*) ; 

__attribute__((used)) static int mls_read_level(struct mls_level *lp, void *fp)
{
	__le32 buf[1];
	int rc;

	memset(lp, 0, sizeof(*lp));

	rc = next_entry(buf, fp, sizeof buf);
	if (rc) {
		pr_err("SELinux: mls: truncated level\n");
		return rc;
	}
	lp->sens = le32_to_cpu(buf[0]);

	rc = ebitmap_read(&lp->cat, fp);
	if (rc) {
		pr_err("SELinux: mls:  error reading level categories\n");
		return rc;
	}
	return 0;
}