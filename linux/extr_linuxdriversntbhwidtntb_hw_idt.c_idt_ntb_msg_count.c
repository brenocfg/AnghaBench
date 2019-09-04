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
struct ntb_dev {int dummy; } ;

/* Variables and functions */
 int IDT_MSG_CNT ; 

__attribute__((used)) static int idt_ntb_msg_count(struct ntb_dev *ntb)
{
	return IDT_MSG_CNT;
}