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
struct qdio_buffer {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  memset (struct qdio_buffer*,int /*<<< orphan*/ ,int) ; 

void qdio_reset_buffers(struct qdio_buffer **buf, unsigned int count)
{
	int pos;

	for (pos = 0; pos < count; pos++)
		memset(buf[pos], 0, sizeof(struct qdio_buffer));
}