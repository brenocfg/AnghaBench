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
typedef  int /*<<< orphan*/  ut8 ;
struct TYPE_3__ {int /*<<< orphan*/  reg; } ;
typedef  TYPE_1__ RDebug ;

/* Variables and functions */
 int /*<<< orphan*/  R_MIN (int,int) ; 
 int /*<<< orphan*/  free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * r_reg_get_bytes (int /*<<< orphan*/ ,int,int*) ; 

__attribute__((used)) static int __reg_read (RDebug *dbg, int type, ut8 *buf, int size) {
	int sz;
	/* do nothing */
	ut8 *bytes = r_reg_get_bytes (dbg->reg, type, &sz);
	memcpy (buf, bytes, R_MIN (size, sz));
	free (bytes);
	return size;
}