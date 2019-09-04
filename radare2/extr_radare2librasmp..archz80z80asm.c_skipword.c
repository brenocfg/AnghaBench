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

/* Variables and functions */
 int /*<<< orphan*/  rd_expr (char const**,char,int*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sp ; 

__attribute__((used)) static void skipword(const char **pos, char delimiter) {
	/* rd_expr will happily read the expression, and possibly return
	 * an invalid result.  It will update pos, which is what we need.  */
	/* Pass valid to allow using undefined labels without errors.  */
	int valid;
	rd_expr (pos, delimiter, &valid, sp, 0);
}