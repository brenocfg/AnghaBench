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
struct v4l2_control {int dummy; } ;

/* Variables and functions */
 int maven_set_control (void*,struct v4l2_control*) ; 

__attribute__((used)) static int maven_out_set_ctrl(void* md, struct v4l2_control* p) {
	return maven_set_control(md, p);
}