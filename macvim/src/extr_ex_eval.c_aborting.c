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
 scalar_t__ did_emsg ; 
 scalar_t__ did_throw ; 
 scalar_t__ force_abort ; 
 scalar_t__ got_int ; 

int
aborting()
{
    return (did_emsg && force_abort) || got_int || did_throw;
}