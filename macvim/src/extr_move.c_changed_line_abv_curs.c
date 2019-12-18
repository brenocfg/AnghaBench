#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {int w_valid; } ;

/* Variables and functions */
 int VALID_CHEIGHT ; 
 int VALID_CROW ; 
 int VALID_TOPLINE ; 
 int VALID_VIRTCOL ; 
 int VALID_WCOL ; 
 int VALID_WROW ; 
 TYPE_1__* curwin ; 

void
changed_line_abv_curs()
{
    curwin->w_valid &= ~(VALID_WROW|VALID_WCOL|VALID_VIRTCOL|VALID_CROW
						|VALID_CHEIGHT|VALID_TOPLINE);
}