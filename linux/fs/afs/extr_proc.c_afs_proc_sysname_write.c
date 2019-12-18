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
struct seq_file {int dummy; } ;
struct file {struct seq_file* private_data; } ;
struct afs_sysnames {size_t nr; char** subs; char* blank; int /*<<< orphan*/  usage; } ;
struct afs_net {int /*<<< orphan*/  sysnames_lock; struct afs_sysnames* sysnames; } ;

/* Variables and functions */
 int AFSNAMEMAX ; 
 size_t AFS_NR_SYSNAME ; 
 int EFBIG ; 
 int EINVAL ; 
 int ENAMETOOLONG ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 scalar_t__ afs_init_sysname ; 
 int /*<<< orphan*/  afs_put_sysnames (struct afs_sysnames*) ; 
 struct afs_net* afs_seq2net (struct seq_file*) ; 
 char* kmemdup (char*,int,int /*<<< orphan*/ ) ; 
 struct afs_sysnames* kzalloc (int,int /*<<< orphan*/ ) ; 
 scalar_t__ memchr (char*,char,int) ; 
 int /*<<< orphan*/  refcount_set (int /*<<< orphan*/ *,int) ; 
 scalar_t__ strcmp (char*,scalar_t__) ; 
 int strlen (char*) ; 
 char* strsep (char**,char*) ; 
 int /*<<< orphan*/  write_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  write_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int afs_proc_sysname_write(struct file *file, char *buf, size_t size)
{
	struct afs_sysnames *sysnames, *kill;
	struct seq_file *m = file->private_data;
	struct afs_net *net = afs_seq2net(m);
	char *s, *p, *sub;
	int ret, len;

	sysnames = kzalloc(sizeof(*sysnames), GFP_KERNEL);
	if (!sysnames)
		return -ENOMEM;
	refcount_set(&sysnames->usage, 1);
	kill = sysnames;

	p = buf;
	while ((s = strsep(&p, " \t\n"))) {
		len = strlen(s);
		if (len == 0)
			continue;
		ret = -ENAMETOOLONG;
		if (len >= AFSNAMEMAX)
			goto error;

		if (len >= 4 &&
		    s[len - 4] == '@' &&
		    s[len - 3] == 's' &&
		    s[len - 2] == 'y' &&
		    s[len - 1] == 's')
			/* Protect against recursion */
			goto invalid;

		if (s[0] == '.' &&
		    (len < 2 || (len == 2 && s[1] == '.')))
			goto invalid;

		if (memchr(s, '/', len))
			goto invalid;

		ret = -EFBIG;
		if (sysnames->nr >= AFS_NR_SYSNAME)
			goto out;

		if (strcmp(s, afs_init_sysname) == 0) {
			sub = (char *)afs_init_sysname;
		} else {
			ret = -ENOMEM;
			sub = kmemdup(s, len + 1, GFP_KERNEL);
			if (!sub)
				goto out;
		}

		sysnames->subs[sysnames->nr] = sub;
		sysnames->nr++;
	}

	if (sysnames->nr == 0) {
		sysnames->subs[0] = sysnames->blank;
		sysnames->nr++;
	}

	write_lock(&net->sysnames_lock);
	kill = net->sysnames;
	net->sysnames = sysnames;
	write_unlock(&net->sysnames_lock);
	ret = 0;
out:
	afs_put_sysnames(kill);
	return ret;

invalid:
	ret = -EINVAL;
error:
	goto out;
}