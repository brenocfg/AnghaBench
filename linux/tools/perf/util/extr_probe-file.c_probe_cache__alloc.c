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
struct probe_cache {int /*<<< orphan*/  fd; int /*<<< orphan*/  entries; } ;

/* Variables and functions */
 int /*<<< orphan*/  EINVAL ; 
 int /*<<< orphan*/  INIT_LIST_HEAD (int /*<<< orphan*/ *) ; 
 struct probe_cache* zalloc (int) ; 

__attribute__((used)) static struct probe_cache *probe_cache__alloc(void)
{
	struct probe_cache *pcache = zalloc(sizeof(*pcache));

	if (pcache) {
		INIT_LIST_HEAD(&pcache->entries);
		pcache->fd = -EINVAL;
	}
	return pcache;
}