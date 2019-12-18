#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  ut8 ;
struct TYPE_5__ {scalar_t__ data; } ;
struct TYPE_4__ {scalar_t__ offset; scalar_t__ size; } ;
typedef  TYPE_1__ RIONull ;
typedef  TYPE_2__ RIODesc ;
typedef  int /*<<< orphan*/  RIO ;

/* Variables and functions */

__attribute__((used)) static int __write(RIO* io, RIODesc* fd, const ut8* buf, int count) {
	RIONull* null;
	if (!fd || !fd->data || !buf) {
		return -1;
	}
	null = (RIONull*) fd->data;
	if ((null->offset + count) > null->size) {
		int ret = null->size - null->offset;
		return ret;
	}
	null->offset += count;
	return count;
}