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
 scalar_t__ const_wanted ; 
 int /*<<< orphan*/  expr_lor () ; 
 int /*<<< orphan*/  expr_lor_const () ; 
 int /*<<< orphan*/  gexpr () ; 
 int /*<<< orphan*/  gnu_ext ; 
 int /*<<< orphan*/  next () ; 
 int /*<<< orphan*/  skip (char) ; 
 char tok ; 
 int /*<<< orphan*/  vdup () ; 

__attribute__((used)) static void expr_cond(void) {
	if (const_wanted) {
		expr_lor_const ();
		if (tok == '?') {
			vdup ();
			next ();
			if (tok != ':' || !gnu_ext) {
				gexpr ();
			}
			skip (':');
			expr_cond ();
		}
	} else {
		expr_lor ();
	}
}