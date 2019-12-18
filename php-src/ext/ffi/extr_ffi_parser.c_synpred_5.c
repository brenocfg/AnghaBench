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
 int _synpred_5 (int) ; 
 int yy_line ; 
 unsigned char const* yy_pos ; 
 unsigned char const* yy_text ; 

__attribute__((used)) static int synpred_5(int sym) {
	int ret;
	const unsigned char *save_pos;
	const unsigned char *save_text;
	int   save_line;

	save_pos  = yy_pos;
	save_text = yy_text;
	save_line = yy_line;
	ret = _synpred_5(sym) != -1;
	yy_pos  = save_pos;
	yy_text = save_text;
	yy_line = save_line;
	return ret;
}