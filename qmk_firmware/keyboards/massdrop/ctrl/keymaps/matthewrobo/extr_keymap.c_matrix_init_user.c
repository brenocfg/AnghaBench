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
 int /*<<< orphan*/  autoshift_disable () ; 
 int /*<<< orphan*/  rgb_matrix_sethsv (int,int,int) ; 

void matrix_init_user(void)
{
	autoshift_disable();
	rgb_matrix_sethsv(128, 255, 255);
	// rgb_matrix_sethsv(192, 112, 255);
	// rgb_matrix_mode(4);
}