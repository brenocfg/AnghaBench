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
 size_t get_choice (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 size_t mouse_choice ; 
 int /*<<< orphan*/ * mouse_choices ; 
 int /*<<< orphan*/  mouse_text ; 

__attribute__((used)) static void
change_mouse_choice(int idx)
{
    mouse_choice = get_choice(mouse_choices, TABLE_SIZE(mouse_choices));
    alloc_text(idx, mouse_text, mouse_choices[mouse_choice]);
}