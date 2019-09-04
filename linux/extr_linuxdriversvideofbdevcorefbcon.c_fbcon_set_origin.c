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
struct vc_data {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  fbcon_scrolldelta (struct vc_data*,scalar_t__) ; 
 scalar_t__ softback_lines ; 

__attribute__((used)) static int fbcon_set_origin(struct vc_data *vc)
{
	if (softback_lines)
		fbcon_scrolldelta(vc, softback_lines);
	return 0;
}