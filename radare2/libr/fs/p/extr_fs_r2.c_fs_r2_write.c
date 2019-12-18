#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_4__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  ut8 ;
typedef  int /*<<< orphan*/  ut64 ;
struct TYPE_7__ {int (* write ) (TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/  const*,int) ;scalar_t__ path; } ;
struct TYPE_6__ {char* path; char* name; } ;
typedef  TYPE_1__ RFSFile ;

/* Variables and functions */
 TYPE_4__* routes ; 
 scalar_t__ strlen (scalar_t__) ; 
 int /*<<< orphan*/  strncmp (char const*,scalar_t__,scalar_t__) ; 
 int stub1 (TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/  const*,int) ; 
 int stub2 (TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/  const*,int) ; 

__attribute__((used)) static bool fs_r2_write(RFSFile *file, ut64 addr, const ut8 *data, int len) {
	int i;
	const char *path = file->path;
	const char *name = file->name;
	for (i = 0; routes[i].path; i++) {
		if (routes[i].write) {
			if (!strncmp (name, routes[i].path + 1, strlen (routes[i].path) - 1)) {
				return routes[i].write (file, addr, data, len);
			}
			if (!strncmp (path, routes[i].path, strlen (routes[i].path))) {
				return routes[i].write (file, addr, data, len);
			}
		}
	}
	return false;
}