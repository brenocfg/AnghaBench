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
typedef  int /*<<< orphan*/  SB ;

/* Variables and functions */
 scalar_t__ number_is_valid (char*) ; 
 int /*<<< orphan*/  sb_puts (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  sprintf (char*,char*,double) ; 

__attribute__((used)) static void emit_number(SB *out, double num)
{
	/*
	 * This isn't exactly how JavaScript renders numbers,
	 * but it should produce valid JSON for reasonable numbers
	 * preserve precision well enough, and avoid some oddities
	 * like 0.3 -> 0.299999999999999988898 .
	 */
	char buf[64];
	sprintf(buf, "%.16g", num);
	
	if (number_is_valid(buf))
		sb_puts(out, buf);
	else
		sb_puts(out, "null");
}