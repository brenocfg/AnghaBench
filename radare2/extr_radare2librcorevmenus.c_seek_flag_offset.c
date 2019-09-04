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
struct seek_flag_offset_t {scalar_t__* next; scalar_t__ offset; scalar_t__ is_next; } ;
struct TYPE_3__ {scalar_t__ offset; } ;
typedef  TYPE_1__ RFlagItem ;

/* Variables and functions */

__attribute__((used)) static bool seek_flag_offset(RFlagItem *fi, void *user) {
	struct seek_flag_offset_t *u = (struct seek_flag_offset_t *)user;
	if (u->is_next) {
		if (fi->offset < *u->next && fi->offset > u->offset) {
			*u->next = fi->offset;
		}
	} else {
		if (fi->offset > *u->next && fi->offset < u->offset) {
			*u->next = fi->offset;
		}
	}
	return true;
}