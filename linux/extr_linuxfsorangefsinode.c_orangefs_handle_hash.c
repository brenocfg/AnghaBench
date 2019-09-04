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
struct orangefs_object_kref {int /*<<< orphan*/  khandle; } ;
typedef  int /*<<< orphan*/  ino_t ;

/* Variables and functions */
 int /*<<< orphan*/  orangefs_khandle_to_ino (int /*<<< orphan*/ *) ; 

__attribute__((used)) static inline ino_t orangefs_handle_hash(struct orangefs_object_kref *ref)
{
	if (!ref)
		return 0;
	return orangefs_khandle_to_ino(&(ref->khandle));
}