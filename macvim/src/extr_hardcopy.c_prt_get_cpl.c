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
 int PRINT_NUMBER_WIDTH ; 
 int prt_char_width ; 
 int prt_left_margin ; 
 int prt_number_width ; 
 scalar_t__ prt_out_mbyte ; 
 int prt_right_margin ; 
 scalar_t__ prt_use_number () ; 

__attribute__((used)) static int
prt_get_cpl()
{
    if (prt_use_number())
    {
	prt_number_width = PRINT_NUMBER_WIDTH * prt_char_width;
#ifdef FEAT_MBYTE
	/* If we are outputting multi-byte characters then line numbers will be
	 * printed with half width characters
	 */
	if (prt_out_mbyte)
	    prt_number_width /= 2;
#endif
	prt_left_margin += prt_number_width;
    }
    else
	prt_number_width = 0.0;

    return (int)((prt_right_margin - prt_left_margin) / prt_char_width);
}