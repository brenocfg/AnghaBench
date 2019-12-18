#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct async_frame {scalar_t__ unused_count; int /*<<< orphan*/  frame; int /*<<< orphan*/  used; } ;
struct TYPE_5__ {size_t num; struct async_frame* array; } ;
struct TYPE_4__ {TYPE_2__ async_cache; } ;
typedef  TYPE_1__ obs_source_t ;

/* Variables and functions */
 scalar_t__ MAX_UNUSED_FRAME_DURATION ; 
 int /*<<< orphan*/  da_erase (TYPE_2__,size_t) ; 
 int /*<<< orphan*/  obs_source_frame_destroy (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void clean_cache(obs_source_t *source)
{
	for (size_t i = source->async_cache.num; i > 0; i--) {
		struct async_frame *af = &source->async_cache.array[i - 1];
		if (!af->used) {
			if (++af->unused_count == MAX_UNUSED_FRAME_DURATION) {
				obs_source_frame_destroy(af->frame);
				da_erase(source->async_cache, i - 1);
			}
		}
	}
}