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
typedef  int /*<<< orphan*/  off_t ;
typedef  int /*<<< orphan*/ * Walfile ;
struct TYPE_2__ {int /*<<< orphan*/  currpos; } ;
typedef  TYPE_1__ DirectoryMethodFile ;

/* Variables and functions */
 int /*<<< orphan*/  Assert (int /*<<< orphan*/ ) ; 

__attribute__((used)) static off_t
dir_get_current_pos(Walfile f)
{
	Assert(f != NULL);

	/* Use a cached value to prevent lots of reseeks */
	return ((DirectoryMethodFile *) f)->currpos;
}