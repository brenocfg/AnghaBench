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
struct frame_rate_option {int /*<<< orphan*/  description; int /*<<< orphan*/  name; } ;
struct TYPE_2__ {size_t num; struct frame_rate_option* array; } ;
struct frame_rate_data {TYPE_1__ extra_options; } ;

/* Variables and functions */
 int /*<<< orphan*/  bfree (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  da_resize (TYPE_1__,int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline void frame_rate_data_options_free(struct frame_rate_data *data)
{
	for (size_t i = 0; i < data->extra_options.num; i++) {
		struct frame_rate_option *opt = &data->extra_options.array[i];
		bfree(opt->name);
		bfree(opt->description);
	}

	da_resize(data->extra_options, 0);
}