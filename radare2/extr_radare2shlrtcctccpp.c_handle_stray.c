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
 scalar_t__ handle_stray_noerror () ; 
 int /*<<< orphan*/  tcc_error (char*) ; 

__attribute__((used)) static void handle_stray(void)
{
	if (handle_stray_noerror ()) {
		tcc_error ("stray '\\' in program");
	}
}