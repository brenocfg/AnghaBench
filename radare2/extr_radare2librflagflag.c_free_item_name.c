#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {scalar_t__ name; scalar_t__ realname; } ;
typedef  TYPE_1__ RFlagItem ;

/* Variables and functions */
 int /*<<< orphan*/  free (scalar_t__) ; 

__attribute__((used)) static void free_item_name(RFlagItem *item) {
	if (item->name != item->realname) {
		free (item->name);
	}
}