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
struct __sk_buff {int data; } ;

/* Variables and functions */
 int TC_ACT_OK ; 

__attribute__((section("action-ko"),used)) int action_ko(struct __sk_buff *s)
{
	s->data = 0x0;
	return TC_ACT_OK;
}