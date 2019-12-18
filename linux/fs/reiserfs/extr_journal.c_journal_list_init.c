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
struct super_block {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  j_current_jl; } ;

/* Variables and functions */
 TYPE_1__* SB_JOURNAL (struct super_block*) ; 
 int /*<<< orphan*/  alloc_journal_list (struct super_block*) ; 

__attribute__((used)) static void journal_list_init(struct super_block *sb)
{
	SB_JOURNAL(sb)->j_current_jl = alloc_journal_list(sb);
}