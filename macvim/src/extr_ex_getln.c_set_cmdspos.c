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
struct TYPE_2__ {scalar_t__ cmdfirstc; scalar_t__ cmdindent; scalar_t__ cmdspos; } ;

/* Variables and functions */
 scalar_t__ NUL ; 
 TYPE_1__ ccline ; 

__attribute__((used)) static void
set_cmdspos()
{
    if (ccline.cmdfirstc != NUL)
	ccline.cmdspos = 1 + ccline.cmdindent;
    else
	ccline.cmdspos = 0 + ccline.cmdindent;
}