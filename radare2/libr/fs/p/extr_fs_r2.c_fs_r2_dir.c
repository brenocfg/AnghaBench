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
struct TYPE_2__ {int /*<<< orphan*/ * (* dir ) (int /*<<< orphan*/ *,char const*) ;scalar_t__ path; } ;
typedef  int /*<<< orphan*/  RList ;
typedef  int /*<<< orphan*/  RFSRoot ;

/* Variables and functions */
 TYPE_1__* routes ; 
 int /*<<< orphan*/  strlen (scalar_t__) ; 
 int /*<<< orphan*/  strncmp (char const*,scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * stub1 (int /*<<< orphan*/ *,char const*) ; 

__attribute__((used)) static RList *fs_r2_dir(RFSRoot *root, const char *path, int view /*ignored*/) {
	int i;
	for (i = 0; routes[i].path; i++) {
		if (routes[i].dir && !strncmp (path, routes[i].path, strlen (routes[i].path))) {
			return routes[i].dir (root, path);
		}
	}
	return NULL;
}