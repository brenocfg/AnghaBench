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
struct TYPE_2__ {int line_end; int len; scalar_t__* buffer; int line_start; } ;

/* Variables and functions */
 scalar_t__ PSCR ; 
 scalar_t__ PSLF ; 
 TYPE_1__ prt_resfile ; 

__attribute__((used)) static int
prt_resfile_next_line()
{
    int     idx;

    /* Move to start of next line and then find end of line */
    idx = prt_resfile.line_end + 1;
    while (idx < prt_resfile.len)
    {
	if (prt_resfile.buffer[idx] != PSLF && prt_resfile.buffer[idx] != PSCR)
	    break;
	idx++;
    }
    prt_resfile.line_start = idx;

    while (idx < prt_resfile.len)
    {
	if (prt_resfile.buffer[idx] == PSLF || prt_resfile.buffer[idx] == PSCR)
	    break;
	idx++;
    }
    prt_resfile.line_end = idx;

    return (idx < prt_resfile.len);
}