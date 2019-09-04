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
typedef  int /*<<< orphan*/  ctlx_usercb_t ;
typedef  int /*<<< orphan*/  ctlx_cmdcb_t ;

/* Variables and functions */
 int /*<<< orphan*/  DOASYNC ; 
 int hfa384x_docmd (struct hfa384x*,int /*<<< orphan*/ ,struct hfa384x_metacmd*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,void*) ; 

__attribute__((used)) static inline int
hfa384x_docmd_async(struct hfa384x *hw,
		    struct hfa384x_metacmd *cmd,
		    ctlx_cmdcb_t cmdcb, ctlx_usercb_t usercb, void *usercb_data)
{
	return hfa384x_docmd(hw, DOASYNC, cmd, cmdcb, usercb, usercb_data);
}