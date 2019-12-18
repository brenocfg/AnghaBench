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
typedef  int /*<<< orphan*/  ut8 ;
typedef  int /*<<< orphan*/  LZ4_stream_t ;

/* Variables and functions */
 int /*<<< orphan*/  LZ4_init (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

int LZ4_resetStreamState(void* state, char* inputBuffer) {
	if ((((size_t)state) & 3) != 0) return 1;   /* Error : pointer is not aligned on 4-bytes boundary */
	LZ4_init((LZ4_stream_t*)state, (ut8*)inputBuffer);
	return 0;
}