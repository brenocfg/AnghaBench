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
struct TYPE_5__ {TYPE_1__* cur; } ;
struct TYPE_4__ {int /*<<< orphan*/  xtr_obj; } ;
typedef  TYPE_2__ RBin ;

/* Variables and functions */
 int /*<<< orphan*/  free_xtr (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void destroy(RBin *bin) {
	free_xtr (bin->cur->xtr_obj);
}