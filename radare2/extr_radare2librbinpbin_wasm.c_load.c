#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {TYPE_1__* o; int /*<<< orphan*/  sdb; int /*<<< orphan*/  buf; } ;
struct TYPE_5__ {int /*<<< orphan*/ * bin_obj; int /*<<< orphan*/  loadaddr; } ;
typedef  TYPE_2__ RBinFile ;

/* Variables and functions */
 int /*<<< orphan*/ * load_buffer (TYPE_2__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  r_return_val_if_fail (int,int) ; 

__attribute__((used)) static bool load(RBinFile *bf) {
	r_return_val_if_fail (bf && bf->o, false);

	bf->o->bin_obj = load_buffer (bf, bf->buf, bf->o->loadaddr, bf->sdb);
	return bf->o->bin_obj != NULL;
}