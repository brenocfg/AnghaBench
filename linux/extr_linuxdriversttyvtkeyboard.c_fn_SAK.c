#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct work_struct {int dummy; } ;
struct vc_data {int dummy; } ;
struct TYPE_2__ {struct work_struct SAK_work; } ;

/* Variables and functions */
 size_t fg_console ; 
 int /*<<< orphan*/  schedule_work (struct work_struct*) ; 
 TYPE_1__* vc_cons ; 

__attribute__((used)) static void fn_SAK(struct vc_data *vc)
{
	struct work_struct *SAK_work = &vc_cons[fg_console].SAK_work;
	schedule_work(SAK_work);
}