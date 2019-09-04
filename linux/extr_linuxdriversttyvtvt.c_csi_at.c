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
struct vc_data {unsigned int vc_cols; unsigned int vc_x; } ;

/* Variables and functions */
 int /*<<< orphan*/  insert_char (struct vc_data*,unsigned int) ; 

__attribute__((used)) static void csi_at(struct vc_data *vc, unsigned int nr)
{
	if (nr > vc->vc_cols - vc->vc_x)
		nr = vc->vc_cols - vc->vc_x;
	else if (!nr)
		nr = 1;
	insert_char(vc, nr);
}