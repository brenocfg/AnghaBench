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
typedef  int /*<<< orphan*/  RIOBind ;

/* Variables and functions */
 int /*<<< orphan*/ * bio ; 
 int /*<<< orphan*/  delta ; 

void grubfs_bind_io (RIOBind *iob, ut64 _delta) {
	bio = iob;
	delta = _delta;
}