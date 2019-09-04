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
struct vc_data {int vc_rows; } ;

/* Variables and functions */
 int /*<<< orphan*/  scrolldelta (int) ; 

void scrollfront(struct vc_data *vc, int lines)
{
	if (!lines)
		lines = vc->vc_rows / 2;
	scrolldelta(lines);
}