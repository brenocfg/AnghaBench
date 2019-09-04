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
struct hfa384x_metacmd {int dummy; } ;
struct hfa384x {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  DOWAIT ; 
 int hfa384x_docmd (struct hfa384x*,int /*<<< orphan*/ ,struct hfa384x_metacmd*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static inline int hfa384x_docmd_wait(struct hfa384x *hw,
				     struct hfa384x_metacmd *cmd)
{
	return hfa384x_docmd(hw, DOWAIT, cmd, NULL, NULL, NULL);
}