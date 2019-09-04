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
 int FALSE ; 
 scalar_t__ mch_print_begin_page (int /*<<< orphan*/ *) ; 
 int mch_print_end_page () ; 

int
mch_print_blank_page()
{
    return (mch_print_begin_page(NULL) ? (mch_print_end_page()) : FALSE);
}