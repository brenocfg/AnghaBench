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
 int YY_COMMENT ; 
 int YY_EOL ; 
 int YY_ONE_LINE_COMMENT ; 
 int YY_WS ; 
 int get_skip_sym () ; 
 int skip_COMMENT (int) ; 
 int skip_EOL (int) ; 
 int skip_ONE_LINE_COMMENT (int) ; 
 int skip_WS (int) ; 

__attribute__((used)) static int get_sym(void) {
	int sym;
	sym = get_skip_sym();
	while (sym == YY_EOL || sym == YY_WS || sym == YY_ONE_LINE_COMMENT || sym == YY_COMMENT) {
		if (sym == YY_EOL) {
			sym = skip_EOL(sym);
		} else if (sym == YY_WS) {
			sym = skip_WS(sym);
		} else if (sym == YY_ONE_LINE_COMMENT) {
			sym = skip_ONE_LINE_COMMENT(sym);
		} else {
			sym = skip_COMMENT(sym);
		}
	}
	return sym;
}