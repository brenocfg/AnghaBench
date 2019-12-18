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
struct aa_profile {int xattr_count; int /*<<< orphan*/ * xattrs; } ;
struct aa_ext {void* pos; } ;

/* Variables and functions */
 int /*<<< orphan*/  AA_ARRAYEND ; 
 int /*<<< orphan*/  AA_STRUCT ; 
 int /*<<< orphan*/  AA_STRUCTEND ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/ * kcalloc (int,int,int /*<<< orphan*/ ) ; 
 int unpack_array (struct aa_ext*,int /*<<< orphan*/ *) ; 
 scalar_t__ unpack_nameX (struct aa_ext*,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  unpack_strdup (struct aa_ext*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static bool unpack_xattrs(struct aa_ext *e, struct aa_profile *profile)
{
	void *pos = e->pos;

	if (unpack_nameX(e, AA_STRUCT, "xattrs")) {
		int i, size;

		size = unpack_array(e, NULL);
		profile->xattr_count = size;
		profile->xattrs = kcalloc(size, sizeof(char *), GFP_KERNEL);
		if (!profile->xattrs)
			goto fail;
		for (i = 0; i < size; i++) {
			if (!unpack_strdup(e, &profile->xattrs[i], NULL))
				goto fail;
		}
		if (!unpack_nameX(e, AA_ARRAYEND, NULL))
			goto fail;
		if (!unpack_nameX(e, AA_STRUCTEND, NULL))
			goto fail;
	}

	return 1;

fail:
	e->pos = pos;
	return 0;
}