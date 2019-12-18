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
typedef  int /*<<< orphan*/  bc_num ;

/* Variables and functions */
 int /*<<< orphan*/  bc_out_num (int /*<<< orphan*/ ,int,int /*<<< orphan*/  (*) (char),int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  out_char (char) ; 

void
pn (bc_num num)
{
  bc_out_num (num, 10, out_char, 0);
  out_char ('\n');
}