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
struct sclp_buffer {void* sccb; } ;

/* Variables and functions */

void *
sclp_unmake_buffer(struct sclp_buffer *buffer)
{
	return buffer->sccb;
}