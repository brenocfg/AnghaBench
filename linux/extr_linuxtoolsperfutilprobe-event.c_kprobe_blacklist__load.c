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
struct list_head {int dummy; } ;
struct kprobe_blacklist_node {int /*<<< orphan*/  symbol; int /*<<< orphan*/  end; int /*<<< orphan*/  start; int /*<<< orphan*/  list; } ;
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 int EINVAL ; 
 int ENOMEM ; 
 int ENOTSUP ; 
 int /*<<< orphan*/  INIT_LIST_HEAD (int /*<<< orphan*/ *) ; 
 int PATH_MAX ; 
 char* debugfs__mountpoint () ; 
 int e_snprintf (char*,int,char*,char const*) ; 
 int errno ; 
 int /*<<< orphan*/  fclose (int /*<<< orphan*/ *) ; 
 scalar_t__ fgets (char*,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * fopen (char*,char*) ; 
 int /*<<< orphan*/  kprobe_blacklist__delete (struct list_head*) ; 
 int /*<<< orphan*/  list_add_tail (int /*<<< orphan*/ *,struct list_head*) ; 
 int /*<<< orphan*/  pr_debug2 (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int sscanf (char*,char*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 char* strchr (char*,char) ; 
 int /*<<< orphan*/  strdup (char*) ; 
 int strlen (char*) ; 
 struct kprobe_blacklist_node* zalloc (int) ; 

__attribute__((used)) static int kprobe_blacklist__load(struct list_head *blacklist)
{
	struct kprobe_blacklist_node *node;
	const char *__debugfs = debugfs__mountpoint();
	char buf[PATH_MAX], *p;
	FILE *fp;
	int ret;

	if (__debugfs == NULL)
		return -ENOTSUP;

	ret = e_snprintf(buf, PATH_MAX, "%s/kprobes/blacklist", __debugfs);
	if (ret < 0)
		return ret;

	fp = fopen(buf, "r");
	if (!fp)
		return -errno;

	ret = 0;
	while (fgets(buf, PATH_MAX, fp)) {
		node = zalloc(sizeof(*node));
		if (!node) {
			ret = -ENOMEM;
			break;
		}
		INIT_LIST_HEAD(&node->list);
		list_add_tail(&node->list, blacklist);
		if (sscanf(buf, "0x%lx-0x%lx", &node->start, &node->end) != 2) {
			ret = -EINVAL;
			break;
		}
		p = strchr(buf, '\t');
		if (p) {
			p++;
			if (p[strlen(p) - 1] == '\n')
				p[strlen(p) - 1] = '\0';
		} else
			p = (char *)"unknown";
		node->symbol = strdup(p);
		if (!node->symbol) {
			ret = -ENOMEM;
			break;
		}
		pr_debug2("Blacklist: 0x%lx-0x%lx, %s\n",
			  node->start, node->end, node->symbol);
		ret++;
	}
	if (ret < 0)
		kprobe_blacklist__delete(blacklist);
	fclose(fp);

	return ret;
}