#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  ut64 ;
struct TYPE_6__ {int (* cat ) (int /*<<< orphan*/ ,TYPE_1__*,char const*) ;scalar_t__ path; } ;
struct TYPE_5__ {char* name; int /*<<< orphan*/  root; } ;
typedef  TYPE_1__ RFSFile ;

/* Variables and functions */
 TYPE_3__* routes ; 
 int /*<<< orphan*/  strlen (scalar_t__) ; 
 int /*<<< orphan*/  strncmp (char const*,scalar_t__,int /*<<< orphan*/ ) ; 
 int stub1 (int /*<<< orphan*/ ,TYPE_1__*,char const*) ; 

__attribute__((used)) static bool fs_r2_read(RFSFile *file, ut64 addr, int len) {
	int i;
	const char *path = file->name;
	for (i = 0; routes[i].path; i++) {
		if (routes[i].cat && !strncmp (path, routes[i].path, strlen (routes[i].path))) {
			return routes[i].cat (file->root, file, path);
		}
	}
	return false;
}