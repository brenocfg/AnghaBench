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
struct vc_data {int vc_top; scalar_t__ vc_decom; } ;

/* Variables and functions */
 int /*<<< orphan*/  gotoxy (struct vc_data*,int,int) ; 

__attribute__((used)) static void gotoxay(struct vc_data *vc, int new_x, int new_y)
{
	gotoxy(vc, new_x, vc->vc_decom ? (vc->vc_top + new_y) : new_y);
}