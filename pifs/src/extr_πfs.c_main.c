#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct options {int dummy; } ;
struct fuse_args {int /*<<< orphan*/  argv; int /*<<< orphan*/  argc; } ;
struct TYPE_4__ {char* mdd; } ;

/* Variables and functions */
 struct fuse_args FUSE_ARGS_INIT (int,char**) ; 
 int R_OK ; 
 int W_OK ; 
 int X_OK ; 
 int access (char*,int) ; 
 int /*<<< orphan*/  errno ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,char*,...) ; 
 int fuse_main (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  fuse_opt_free_args (struct fuse_args*) ; 
 int fuse_opt_parse (struct fuse_args*,TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  memset (TYPE_1__*,int /*<<< orphan*/ ,int) ; 
 TYPE_1__ options ; 
 int /*<<< orphan*/  pifs_ops ; 
 int /*<<< orphan*/  pifs_opts ; 
 int /*<<< orphan*/  stderr ; 
 char* strerror (int /*<<< orphan*/ ) ; 

int main (int argc, char *argv[])
{
  int ret;
  struct fuse_args args = FUSE_ARGS_INIT(argc, argv);

  memset(&options, 0, sizeof(struct options));
  if (fuse_opt_parse(&args, &options, pifs_opts, NULL) == -1) {
    return -1;
  }

  if (!options.mdd) {
    fprintf(stderr,
            "%s: Metadata directory must be specified with -o mdd=<directory>\n",
            argv[0]);
    return -1;
  }

  if (access(options.mdd, R_OK | W_OK | X_OK) == -1) {
    fprintf(stderr, "%s: Cannot access metadata directory '%s': %s\n",
            argv[0], options.mdd, strerror(errno));
    return -1;
  }

  ret = fuse_main(args.argc, args.argv, &pifs_ops, NULL);
  fuse_opt_free_args(&args);
  return ret;
}