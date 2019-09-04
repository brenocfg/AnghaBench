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
typedef  int /*<<< orphan*/  substring_t ;
struct TYPE_4__ {int override_compr; unsigned int rp_size; int /*<<< orphan*/  compr; } ;
struct jffs2_sb_info {TYPE_2__ mount_opts; TYPE_1__* mtd; } ;
struct TYPE_3__ {unsigned int size; } ;

/* Variables and functions */
 int EINVAL ; 
 int ENOMEM ; 
 int /*<<< orphan*/  JFFS2_COMPR_MODE_NONE ; 
 int MAX_OPT_ARGS ; 
#define  Opt_override_compr 129 
#define  Opt_rp_size 128 
 int /*<<< orphan*/  kfree (char*) ; 
 int /*<<< orphan*/  match_int (int /*<<< orphan*/ *,unsigned int*) ; 
 char* match_strdup (int /*<<< orphan*/ *) ; 
 int match_token (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pr_err (char*,char*) ; 
 int /*<<< orphan*/  pr_warn (char*,int) ; 
 int /*<<< orphan*/  strcmp (char*,char*) ; 
 char* strsep (char**,char*) ; 
 int /*<<< orphan*/  tokens ; 

__attribute__((used)) static int jffs2_parse_options(struct jffs2_sb_info *c, char *data)
{
	substring_t args[MAX_OPT_ARGS];
	char *p, *name;
	unsigned int opt;

	if (!data)
		return 0;

	while ((p = strsep(&data, ","))) {
		int token;

		if (!*p)
			continue;

		token = match_token(p, tokens, args);
		switch (token) {
		case Opt_override_compr:
			name = match_strdup(&args[0]);

			if (!name)
				return -ENOMEM;
			if (!strcmp(name, "none"))
				c->mount_opts.compr = JFFS2_COMPR_MODE_NONE;
#ifdef CONFIG_JFFS2_LZO
			else if (!strcmp(name, "lzo"))
				c->mount_opts.compr = JFFS2_COMPR_MODE_FORCELZO;
#endif
#ifdef CONFIG_JFFS2_ZLIB
			else if (!strcmp(name, "zlib"))
				c->mount_opts.compr =
						JFFS2_COMPR_MODE_FORCEZLIB;
#endif
			else {
				pr_err("Error: unknown compressor \"%s\"\n",
				       name);
				kfree(name);
				return -EINVAL;
			}
			kfree(name);
			c->mount_opts.override_compr = true;
			break;
		case Opt_rp_size:
			if (match_int(&args[0], &opt))
				return -EINVAL;
			opt *= 1024;
			if (opt > c->mtd->size) {
				pr_warn("Too large reserve pool specified, max "
					"is %llu KB\n", c->mtd->size / 1024);
				return -EINVAL;
			}
			c->mount_opts.rp_size = opt;
			break;
		default:
			pr_err("Error: unrecognized mount option '%s' or missing value\n",
			       p);
			return -EINVAL;
		}
	}

	return 0;
}