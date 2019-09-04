#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  ut64 ;
struct TYPE_7__ {int /*<<< orphan*/  kernel_addr; } ;
struct TYPE_9__ {TYPE_2__ bi; } ;
struct TYPE_8__ {TYPE_1__* o; } ;
struct TYPE_6__ {TYPE_4__* bin_obj; } ;
typedef  TYPE_3__ RBinFile ;
typedef  TYPE_4__ BootImageObj ;

/* Variables and functions */

__attribute__((used)) static ut64 baddr(RBinFile *bf) {
	BootImageObj *bio = bf->o->bin_obj;
	return bio? bio->bi.kernel_addr: 0;
}