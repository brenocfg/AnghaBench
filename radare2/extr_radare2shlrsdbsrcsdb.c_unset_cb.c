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
struct TYPE_2__ {int /*<<< orphan*/  sdb; int /*<<< orphan*/  key; } ;
typedef  TYPE_1__ UnsetCallbackData ;

/* Variables and functions */
 scalar_t__ sdb_match (char const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sdb_unset (int /*<<< orphan*/ ,char const*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int unset_cb(void *user, const char *k, const char *v) {
	UnsetCallbackData *ucd = user;
	if (sdb_match (k, ucd->key)) {
		sdb_unset (ucd->sdb, k, 0);
	}
	return 1;
}