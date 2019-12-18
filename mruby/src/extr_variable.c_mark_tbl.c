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
typedef  int /*<<< orphan*/  mrb_state ;
typedef  int /*<<< orphan*/  iv_tbl ;

/* Variables and functions */
 int /*<<< orphan*/  iv_foreach (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  iv_mark_i ; 

__attribute__((used)) static void
mark_tbl(mrb_state *mrb, iv_tbl *t)
{
  iv_foreach(mrb, t, iv_mark_i, 0);
}