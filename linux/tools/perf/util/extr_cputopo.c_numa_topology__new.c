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
typedef  int u32 ;
struct perf_cpu_map {int /*<<< orphan*/ * map; scalar_t__ nr; } ;
struct numa_topology {int nr; int /*<<< orphan*/ * nodes; } ;
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 int MAXPATHLEN ; 
 int /*<<< orphan*/  NODE_ONLINE_FMT ; 
 int /*<<< orphan*/  fclose (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * fopen (char*,char*) ; 
 int /*<<< orphan*/  free (char*) ; 
 scalar_t__ getline (char**,size_t*,int /*<<< orphan*/ *) ; 
 scalar_t__ load_numa_node (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  numa_topology__delete (struct numa_topology*) ; 
 struct perf_cpu_map* perf_cpu_map__new (char*) ; 
 int /*<<< orphan*/  perf_cpu_map__put (struct perf_cpu_map*) ; 
 int /*<<< orphan*/  scnprintf (char*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 char* strchr (char*,char) ; 
 int /*<<< orphan*/  sysfs__mountpoint () ; 
 struct numa_topology* zalloc (int) ; 

struct numa_topology *numa_topology__new(void)
{
	struct perf_cpu_map *node_map = NULL;
	struct numa_topology *tp = NULL;
	char path[MAXPATHLEN];
	char *buf = NULL;
	size_t len = 0;
	u32 nr, i;
	FILE *fp;
	char *c;

	scnprintf(path, MAXPATHLEN, NODE_ONLINE_FMT,
		  sysfs__mountpoint());

	fp = fopen(path, "r");
	if (!fp)
		return NULL;

	if (getline(&buf, &len, fp) <= 0)
		goto out;

	c = strchr(buf, '\n');
	if (c)
		*c = '\0';

	node_map = perf_cpu_map__new(buf);
	if (!node_map)
		goto out;

	nr = (u32) node_map->nr;

	tp = zalloc(sizeof(*tp) + sizeof(tp->nodes[0])*nr);
	if (!tp)
		goto out;

	tp->nr = nr;

	for (i = 0; i < nr; i++) {
		if (load_numa_node(&tp->nodes[i], node_map->map[i])) {
			numa_topology__delete(tp);
			tp = NULL;
			break;
		}
	}

out:
	free(buf);
	fclose(fp);
	perf_cpu_map__put(node_map);
	return tp;
}