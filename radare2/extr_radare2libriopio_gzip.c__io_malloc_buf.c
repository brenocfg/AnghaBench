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
struct TYPE_4__ {int /*<<< orphan*/ * buf; } ;
typedef  TYPE_1__ RIOGzip ;
typedef  TYPE_2__ RIODesc ;

/* Variables and functions */

__attribute__((used)) static inline ut8* _io_malloc_buf(RIODesc *desc) {
	if (!desc) {
		return NULL;
	}
	RIOGzip *mal = (RIOGzip*)desc->data;
	return mal->buf;
}