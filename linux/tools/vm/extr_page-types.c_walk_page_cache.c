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
struct stat {int /*<<< orphan*/  st_mode; } ;

/* Variables and functions */
 int FTW_MOUNT ; 
 int FTW_PHYS ; 
 int /*<<< orphan*/  O_RDONLY ; 
 int /*<<< orphan*/  SIGBUS ; 
 int /*<<< orphan*/  SIG_DFL ; 
 scalar_t__ S_ISDIR (int /*<<< orphan*/ ) ; 
 scalar_t__ S_ISREG (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  checked_open (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  close (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fatal (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kpageflags_fd ; 
 scalar_t__ nftw (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  opt_file ; 
 char* opt_kpageflags ; 
 int /*<<< orphan*/  pagemap_fd ; 
 int /*<<< orphan*/  sigaction (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sigbus_action ; 
 int /*<<< orphan*/  signal (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ stat (int /*<<< orphan*/ ,struct stat*) ; 
 int /*<<< orphan*/  walk_file (int /*<<< orphan*/ ,struct stat*) ; 
 int /*<<< orphan*/  walk_tree ; 

__attribute__((used)) static void walk_page_cache(void)
{
	struct stat st;

	kpageflags_fd = checked_open(opt_kpageflags, O_RDONLY);
	pagemap_fd = checked_open("/proc/self/pagemap", O_RDONLY);
	sigaction(SIGBUS, &sigbus_action, NULL);

	if (stat(opt_file, &st))
		fatal("stat failed: %s\n", opt_file);

	if (S_ISREG(st.st_mode)) {
		walk_file(opt_file, &st);
	} else if (S_ISDIR(st.st_mode)) {
		/* do not follow symlinks and mountpoints */
		if (nftw(opt_file, walk_tree, 64, FTW_MOUNT | FTW_PHYS) < 0)
			fatal("nftw failed: %s\n", opt_file);
	} else
		fatal("unhandled file type: %s\n", opt_file);

	close(kpageflags_fd);
	close(pagemap_fd);
	signal(SIGBUS, SIG_DFL);
}