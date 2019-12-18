#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {char* start; char* cur; char* end; } ;
typedef  TYPE_1__ SB ;

/* Variables and functions */
 scalar_t__ malloc (int) ; 
 int /*<<< orphan*/  out_of_memory () ; 

__attribute__((used)) static void sb_init(SB *sb)
{
	sb->start = (char*) malloc(17);
	if (sb->start == NULL)
		out_of_memory();
	sb->cur = sb->start;
	sb->end = sb->start + 16;
}