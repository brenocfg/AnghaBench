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
typedef  int uint64_t ;
struct flv_output {int stop_ts; int /*<<< orphan*/  stopping; } ;

/* Variables and functions */
 int /*<<< orphan*/  os_atomic_set_bool (int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static void flv_output_stop(void *data, uint64_t ts)
{
	struct flv_output *stream = data;
	stream->stop_ts = ts / 1000;
	os_atomic_set_bool(&stream->stopping, true);
}