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
typedef  int /*<<< orphan*/  mpc_parser_t ;

/* Variables and functions */
 int /*<<< orphan*/  mpc_print_unretained (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  printf (char*) ; 

void mpc_print(mpc_parser_t *p) {
  mpc_print_unretained(p, 1);
  printf("\n");
}