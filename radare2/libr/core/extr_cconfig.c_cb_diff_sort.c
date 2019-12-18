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
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {char* value; } ;
struct TYPE_5__ {TYPE_1__* anal; } ;
struct TYPE_4__ {void* columnSort; } ;
typedef  void* RListComparator ;
typedef  TYPE_2__ RCore ;
typedef  TYPE_3__ RConfigNode ;

/* Variables and functions */
 scalar_t__ compareAddress ; 
 scalar_t__ compareDist ; 
 scalar_t__ compareName ; 
 scalar_t__ compareNameLen ; 
 scalar_t__ compareSize ; 
 scalar_t__ compareType ; 
 int /*<<< orphan*/  eprintf (char*) ; 
 scalar_t__ strcmp (char const*,char*) ; 

__attribute__((used)) static bool cb_diff_sort(void *_core, void *_node) {
	RConfigNode *node = _node;
	const char *column = node->value;
	RCore *core = _core;
	if (column && strcmp (column, "?")) {
		if (!strcmp (column, "name")) {
			core->anal->columnSort = (RListComparator)compareName;
		} else if (!strcmp (column, "namelen")) {
			core->anal->columnSort = (RListComparator)compareNameLen;
		} else if (!strcmp (column, "addr")) {
			core->anal->columnSort = (RListComparator)compareAddress;
		} else if (!strcmp (column, "type")) {
			core->anal->columnSort = (RListComparator)compareType;
		} else if (!strcmp (column, "size")) {
			core->anal->columnSort = (RListComparator)compareSize;
		} else if (!strcmp (column, "dist")) {
			core->anal->columnSort = (RListComparator)compareDist;
		} else {
			goto fail;
		}
		return true;
	}
fail:
	eprintf ("e diff.sort = [name, namelen, addr, type, size, dist]\n");
	return false;
}