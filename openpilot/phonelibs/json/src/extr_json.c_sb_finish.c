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
struct TYPE_3__ {char* cur; char* start; } ;
typedef  TYPE_1__ SB ;

/* Variables and functions */
 int /*<<< orphan*/  assert (int) ; 
 size_t strlen (char*) ; 

__attribute__((used)) static char *sb_finish(SB *sb)
{
	*sb->cur = 0;
	assert(sb->start <= sb->cur && strlen(sb->start) == (size_t)(sb->cur - sb->start));
	return sb->start;
}