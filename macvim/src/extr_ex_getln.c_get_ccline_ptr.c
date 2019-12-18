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
struct cmdline_info {int /*<<< orphan*/ * cmdbuff; } ;

/* Variables and functions */
 int CMDLINE ; 
 int State ; 
 struct cmdline_info ccline ; 
 struct cmdline_info prev_ccline ; 
 scalar_t__ prev_ccline_used ; 

__attribute__((used)) static struct cmdline_info *
get_ccline_ptr()
{
    if ((State & CMDLINE) == 0)
	return NULL;
    if (ccline.cmdbuff != NULL)
	return &ccline;
    if (prev_ccline_used && prev_ccline.cmdbuff != NULL)
	return &prev_ccline;
    return NULL;
}