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
typedef  enum cfg_options_flags { ____Placeholder_cfg_options_flags } cfg_options_flags ;

/* Variables and functions */
 int /*<<< orphan*/  EXIT_FAIL ; 
 int NO_TOUCH ; 
 int READ_MEM ; 
 int SWAP_MAC ; 
 int /*<<< orphan*/  exit (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  stderr ; 

__attribute__((used)) static char* options2str(enum cfg_options_flags flag)
{
	if (flag == NO_TOUCH)
		return "no_touch";
	if (flag & SWAP_MAC)
		return "swapmac";
	if (flag & READ_MEM)
		return "read";
	fprintf(stderr, "ERR: Unknown config option flags");
	exit(EXIT_FAIL);
}