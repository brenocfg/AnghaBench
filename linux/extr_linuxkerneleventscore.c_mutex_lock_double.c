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
struct mutex {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  SINGLE_DEPTH_NESTING ; 
 int /*<<< orphan*/  mutex_lock (struct mutex*) ; 
 int /*<<< orphan*/  mutex_lock_nested (struct mutex*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  swap (struct mutex*,struct mutex*) ; 

__attribute__((used)) static void mutex_lock_double(struct mutex *a, struct mutex *b)
{
	if (b < a)
		swap(a, b);

	mutex_lock(a);
	mutex_lock_nested(b, SINGLE_DEPTH_NESTING);
}