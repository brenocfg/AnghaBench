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
typedef  int /*<<< orphan*/  substring_t ;
struct btrfs_device {int dummy; } ;
typedef  int /*<<< orphan*/  fmode_t ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 scalar_t__ IS_ERR (struct btrfs_device*) ; 
 int MAX_OPT_ARGS ; 
 int Opt_device ; 
 int PTR_ERR (struct btrfs_device*) ; 
 struct btrfs_device* btrfs_scan_one_device (char*,int /*<<< orphan*/ ,void*) ; 
 int /*<<< orphan*/  kfree (char*) ; 
 char* kstrdup (char const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lockdep_assert_held (int /*<<< orphan*/ *) ; 
 char* match_strdup (int /*<<< orphan*/ *) ; 
 int match_token (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 char* strsep (char**,char*) ; 
 int /*<<< orphan*/  tokens ; 
 int /*<<< orphan*/  uuid_mutex ; 

__attribute__((used)) static int btrfs_parse_device_options(const char *options, fmode_t flags,
				      void *holder)
{
	substring_t args[MAX_OPT_ARGS];
	char *device_name, *opts, *orig, *p;
	struct btrfs_device *device = NULL;
	int error = 0;

	lockdep_assert_held(&uuid_mutex);

	if (!options)
		return 0;

	/*
	 * strsep changes the string, duplicate it because btrfs_parse_options
	 * gets called later
	 */
	opts = kstrdup(options, GFP_KERNEL);
	if (!opts)
		return -ENOMEM;
	orig = opts;

	while ((p = strsep(&opts, ",")) != NULL) {
		int token;

		if (!*p)
			continue;

		token = match_token(p, tokens, args);
		if (token == Opt_device) {
			device_name = match_strdup(&args[0]);
			if (!device_name) {
				error = -ENOMEM;
				goto out;
			}
			device = btrfs_scan_one_device(device_name, flags,
					holder);
			kfree(device_name);
			if (IS_ERR(device)) {
				error = PTR_ERR(device);
				goto out;
			}
		}
	}

out:
	kfree(orig);
	return error;
}