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
typedef  int uint8_t ;
struct TYPE_3__ {int check; } ;
typedef  TYPE_1__ lzma_stream_flags ;

/* Variables and functions */
 unsigned int LZMA_CHECK_ID_MAX ; 

__attribute__((used)) static bool
stream_flags_encode(const lzma_stream_flags *options, uint8_t *out)
{
	if ((unsigned int)(options->check) > LZMA_CHECK_ID_MAX)
		return true;

	out[0] = 0x00;
	out[1] = options->check;

	return false;
}