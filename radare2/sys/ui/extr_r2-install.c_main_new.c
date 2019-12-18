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
typedef  int /*<<< orphan*/  Main ;

/* Variables and functions */
 int /*<<< orphan*/  TYPE_MAIN ; 
 int /*<<< orphan*/ * main_construct (int /*<<< orphan*/ ) ; 

Main* main_new (void) {
	return main_construct (TYPE_MAIN);
}