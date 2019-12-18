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
typedef  int /*<<< orphan*/  uint64_t ;
struct TYPE_3__ {int /*<<< orphan*/  image; } ;
typedef  TYPE_1__ gs_image_file2_t ;

/* Variables and functions */
 int gs_image_file_tick (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline bool gs_image_file2_tick(gs_image_file2_t *if2,
				       uint64_t elapsed_time_ns)
{
	return gs_image_file_tick(&if2->image, elapsed_time_ns);
}