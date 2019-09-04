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
struct dotl_iattr_map {int iattr_valid; int p9_iattr_valid; int /*<<< orphan*/  member_1; int /*<<< orphan*/  member_0; } ;

/* Variables and functions */
 int ARRAY_SIZE (struct dotl_iattr_map*) ; 
 int /*<<< orphan*/  ATTR_ATIME ; 
 int /*<<< orphan*/  ATTR_ATIME_SET ; 
 int /*<<< orphan*/  ATTR_CTIME ; 
 int /*<<< orphan*/  ATTR_GID ; 
 int /*<<< orphan*/  ATTR_MODE ; 
 int /*<<< orphan*/  ATTR_MTIME ; 
 int /*<<< orphan*/  ATTR_MTIME_SET ; 
 int /*<<< orphan*/  ATTR_SIZE ; 
 int /*<<< orphan*/  ATTR_UID ; 
 int /*<<< orphan*/  P9_ATTR_ATIME ; 
 int /*<<< orphan*/  P9_ATTR_ATIME_SET ; 
 int /*<<< orphan*/  P9_ATTR_CTIME ; 
 int /*<<< orphan*/  P9_ATTR_GID ; 
 int /*<<< orphan*/  P9_ATTR_MODE ; 
 int /*<<< orphan*/  P9_ATTR_MTIME ; 
 int /*<<< orphan*/  P9_ATTR_MTIME_SET ; 
 int /*<<< orphan*/  P9_ATTR_SIZE ; 
 int /*<<< orphan*/  P9_ATTR_UID ; 

__attribute__((used)) static int v9fs_mapped_iattr_valid(int iattr_valid)
{
	int i;
	int p9_iattr_valid = 0;
	struct dotl_iattr_map dotl_iattr_map[] = {
		{ ATTR_MODE,		P9_ATTR_MODE },
		{ ATTR_UID,		P9_ATTR_UID },
		{ ATTR_GID,		P9_ATTR_GID },
		{ ATTR_SIZE,		P9_ATTR_SIZE },
		{ ATTR_ATIME,		P9_ATTR_ATIME },
		{ ATTR_MTIME,		P9_ATTR_MTIME },
		{ ATTR_CTIME,		P9_ATTR_CTIME },
		{ ATTR_ATIME_SET,	P9_ATTR_ATIME_SET },
		{ ATTR_MTIME_SET,	P9_ATTR_MTIME_SET },
	};
	for (i = 0; i < ARRAY_SIZE(dotl_iattr_map); i++) {
		if (iattr_valid & dotl_iattr_map[i].iattr_valid)
			p9_iattr_valid |= dotl_iattr_map[i].p9_iattr_valid;
	}
	return p9_iattr_valid;
}