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
struct strbuf {int dummy; } ;
struct list_head {int dummy; } ;

/* Variables and functions */
 int EINVAL ; 
 int ENOMEM ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,char*) ; 
 int /*<<< orphan*/  free (char*) ; 
 int metricgroup__add_metric (char*,struct strbuf*,struct list_head*) ; 
 int /*<<< orphan*/  stderr ; 
 int /*<<< orphan*/  strbuf_addf (struct strbuf*,char*,char*) ; 
 int /*<<< orphan*/  strbuf_init (struct strbuf*,int) ; 
 char* strdup (char const*) ; 
 char* strsep (char**,char*) ; 

__attribute__((used)) static int metricgroup__add_metric_list(const char *list, struct strbuf *events,
				        struct list_head *group_list)
{
	char *llist, *nlist, *p;
	int ret = -EINVAL;

	nlist = strdup(list);
	if (!nlist)
		return -ENOMEM;
	llist = nlist;

	strbuf_init(events, 100);
	strbuf_addf(events, "%s", "");

	while ((p = strsep(&llist, ",")) != NULL) {
		ret = metricgroup__add_metric(p, events, group_list);
		if (ret == -EINVAL) {
			fprintf(stderr, "Cannot find metric or group `%s'\n",
					p);
			break;
		}
	}
	free(nlist);
	return ret;
}