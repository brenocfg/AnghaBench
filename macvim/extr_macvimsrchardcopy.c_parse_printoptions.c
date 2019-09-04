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
typedef  int /*<<< orphan*/  char_u ;

/* Variables and functions */
 int /*<<< orphan*/  OPT_PRINT_NUM_OPTIONS ; 
 int /*<<< orphan*/  p_popt ; 
 int /*<<< orphan*/ * parse_list_options (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  printer_opts ; 

char_u *
parse_printoptions()
{
    return parse_list_options(p_popt, printer_opts, OPT_PRINT_NUM_OPTIONS);
}