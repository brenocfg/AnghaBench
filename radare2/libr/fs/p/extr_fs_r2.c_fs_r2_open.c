#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {char* path; int /*<<< orphan*/ * (* cat ) (int /*<<< orphan*/ *,int /*<<< orphan*/ *,char const*) ;} ;
typedef  int /*<<< orphan*/  RFSRoot ;
typedef  int /*<<< orphan*/  RFSFile ;

/* Variables and functions */
 TYPE_1__* routes ; 
 int /*<<< orphan*/  strlen (char const*) ; 
 int /*<<< orphan*/  strncmp (char const*,char const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * stub1 (int /*<<< orphan*/ *,int /*<<< orphan*/ *,char const*) ; 

__attribute__((used)) static RFSFile* fs_r2_open(RFSRoot *root, const char *path, bool create) {
	int i;
	for (i = 0; routes[i].path; i++) {
		const char *cwd = routes[i].path;
		if (routes[i].cat && !strncmp (path, cwd, strlen (cwd))) {
			return routes[i].cat (root, NULL, path);
		}
	}
	return NULL;
}