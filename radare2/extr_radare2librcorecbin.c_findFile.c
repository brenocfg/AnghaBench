#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  ut32 ;
struct TYPE_4__ {TYPE_1__* desc; int /*<<< orphan*/  uri; scalar_t__ perm; } ;
struct TYPE_3__ {int /*<<< orphan*/  uri; scalar_t__ perm; } ;
typedef  TYPE_1__ RIODesc ;
typedef  TYPE_2__ FindFile ;

/* Variables and functions */
 int /*<<< orphan*/  strcmp (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static bool findFile(void *user, void *data, ut32 id) {
	FindFile *res = (FindFile*)user;
	RIODesc *desc = (RIODesc*)data;
	if (desc->perm && res->perm && !strcmp (desc->uri, res->uri)) {
		res->desc = desc;
		return false;
	}
	return true;
}