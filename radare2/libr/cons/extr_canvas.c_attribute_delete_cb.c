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
typedef  int /*<<< orphan*/  ut64 ;
typedef  int /*<<< orphan*/  HtUP ;

/* Variables and functions */
 int /*<<< orphan*/  ht_up_delete (int /*<<< orphan*/ *,int /*<<< orphan*/  const) ; 

__attribute__((used)) static bool attribute_delete_cb(void *user, const ut64 key, const void *value) {
	HtUP *ht = (HtUP *)user;
	ht_up_delete (ht, key);
	return true;
}