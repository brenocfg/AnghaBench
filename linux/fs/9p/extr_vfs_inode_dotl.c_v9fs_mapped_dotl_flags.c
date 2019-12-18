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
struct dotl_openflag_map {int open_flag; int dotl_flag; int /*<<< orphan*/  member_1; int /*<<< orphan*/  member_0; } ;

/* Variables and functions */
 int ARRAY_SIZE (struct dotl_openflag_map*) ; 
 int /*<<< orphan*/  FASYNC ; 
 int /*<<< orphan*/  O_APPEND ; 
 int /*<<< orphan*/  O_CLOEXEC ; 
 int /*<<< orphan*/  O_CREAT ; 
 int /*<<< orphan*/  O_DIRECT ; 
 int /*<<< orphan*/  O_DIRECTORY ; 
 int /*<<< orphan*/  O_DSYNC ; 
 int /*<<< orphan*/  O_EXCL ; 
 int /*<<< orphan*/  O_LARGEFILE ; 
 int /*<<< orphan*/  O_NOATIME ; 
 int /*<<< orphan*/  O_NOCTTY ; 
 int /*<<< orphan*/  O_NOFOLLOW ; 
 int /*<<< orphan*/  O_NONBLOCK ; 
 int /*<<< orphan*/  O_SYNC ; 
 int /*<<< orphan*/  P9_DOTL_APPEND ; 
 int /*<<< orphan*/  P9_DOTL_CLOEXEC ; 
 int /*<<< orphan*/  P9_DOTL_CREATE ; 
 int /*<<< orphan*/  P9_DOTL_DIRECT ; 
 int /*<<< orphan*/  P9_DOTL_DIRECTORY ; 
 int /*<<< orphan*/  P9_DOTL_DSYNC ; 
 int /*<<< orphan*/  P9_DOTL_EXCL ; 
 int /*<<< orphan*/  P9_DOTL_FASYNC ; 
 int /*<<< orphan*/  P9_DOTL_LARGEFILE ; 
 int /*<<< orphan*/  P9_DOTL_NOATIME ; 
 int /*<<< orphan*/  P9_DOTL_NOCTTY ; 
 int /*<<< orphan*/  P9_DOTL_NOFOLLOW ; 
 int /*<<< orphan*/  P9_DOTL_NONBLOCK ; 
 int /*<<< orphan*/  P9_DOTL_SYNC ; 

__attribute__((used)) static int v9fs_mapped_dotl_flags(int flags)
{
	int i;
	int rflags = 0;
	struct dotl_openflag_map dotl_oflag_map[] = {
		{ O_CREAT,	P9_DOTL_CREATE },
		{ O_EXCL,	P9_DOTL_EXCL },
		{ O_NOCTTY,	P9_DOTL_NOCTTY },
		{ O_APPEND,	P9_DOTL_APPEND },
		{ O_NONBLOCK,	P9_DOTL_NONBLOCK },
		{ O_DSYNC,	P9_DOTL_DSYNC },
		{ FASYNC,	P9_DOTL_FASYNC },
		{ O_DIRECT,	P9_DOTL_DIRECT },
		{ O_LARGEFILE,	P9_DOTL_LARGEFILE },
		{ O_DIRECTORY,	P9_DOTL_DIRECTORY },
		{ O_NOFOLLOW,	P9_DOTL_NOFOLLOW },
		{ O_NOATIME,	P9_DOTL_NOATIME },
		{ O_CLOEXEC,	P9_DOTL_CLOEXEC },
		{ O_SYNC,	P9_DOTL_SYNC},
	};
	for (i = 0; i < ARRAY_SIZE(dotl_oflag_map); i++) {
		if (flags & dotl_oflag_map[i].open_flag)
			rflags |= dotl_oflag_map[i].dotl_flag;
	}
	return rflags;
}