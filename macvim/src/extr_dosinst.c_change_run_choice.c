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

/* Variables and functions */
 int /*<<< orphan*/  TABLE_SIZE (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  alloc_text (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 size_t compat_choice ; 
 int /*<<< orphan*/ * compat_choices ; 
 int /*<<< orphan*/  compat_text ; 
 size_t get_choice (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
change_run_choice(int idx)
{
    compat_choice = get_choice(compat_choices, TABLE_SIZE(compat_choices));
    alloc_text(idx, compat_text, compat_choices[compat_choice]);
}