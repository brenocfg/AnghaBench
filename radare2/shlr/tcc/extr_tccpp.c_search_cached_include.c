#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int hash_next; int /*<<< orphan*/  filename; } ;
struct TYPE_5__ {int* cached_includes_hash; TYPE_2__** cached_includes; } ;
typedef  TYPE_1__ TCCState ;
typedef  TYPE_2__ CachedInclude ;

/* Variables and functions */
 scalar_t__ PATHCMP (int /*<<< orphan*/ ,char const*) ; 
 int hash_cached_include (char const*) ; 

__attribute__((used)) static CachedInclude *search_cached_include(TCCState *s1, const char *filename)
{
	CachedInclude *e;
	int i, h;
	h = hash_cached_include (filename);
	i = s1->cached_includes_hash[h];
	for (;;) {
		if (i == 0) {
			break;
		}
		e = s1->cached_includes[i - 1];
		if (0 == PATHCMP (e->filename, filename)) {
			return e;
		}
		i = e->hash_next;
	}
	return NULL;
}