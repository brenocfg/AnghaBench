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
typedef  scalar_t__ ut64 ;
struct TYPE_3__ {int /*<<< orphan*/  anal; scalar_t__ blocksize; } ;
typedef  TYPE_1__ RCore ;

/* Variables and functions */
 int /*<<< orphan*/  R_META_TYPE_DATA ; 
 int /*<<< orphan*/  r_meta_add (int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__,scalar_t__,char*) ; 
 int /*<<< orphan*/  r_meta_cleanup (int /*<<< orphan*/ ,scalar_t__,scalar_t__) ; 

__attribute__((used)) static void define_data_ntimes (RCore *core, ut64 off, int times, int type) {
	int i = 0;
	r_meta_cleanup (core->anal, off, off + core->blocksize);
	if (times < 0) {
		times = 1;
	}
	for (i = 0; i < times; i++, off += type) {
		r_meta_add (core->anal, R_META_TYPE_DATA, off, off + type, "");
	}
}