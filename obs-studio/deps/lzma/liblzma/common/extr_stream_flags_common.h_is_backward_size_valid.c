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
struct TYPE_3__ {int backward_size; } ;
typedef  TYPE_1__ lzma_stream_flags ;

/* Variables and functions */
 int LZMA_BACKWARD_SIZE_MAX ; 
 int LZMA_BACKWARD_SIZE_MIN ; 

__attribute__((used)) static inline bool
is_backward_size_valid(const lzma_stream_flags *options)
{
	return options->backward_size >= LZMA_BACKWARD_SIZE_MIN
			&& options->backward_size <= LZMA_BACKWARD_SIZE_MAX
			&& (options->backward_size & 3) == 0;
}