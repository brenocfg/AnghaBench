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
 size_t remap_choice ; 
 int /*<<< orphan*/ * remap_choices ; 
 int /*<<< orphan*/  remap_text ; 

__attribute__((used)) static void
change_remap_choice(int idx)
{
    remap_choice = get_choice(remap_choices, TABLE_SIZE(remap_choices));
    alloc_text(idx, remap_text, remap_choices[remap_choice]);
}