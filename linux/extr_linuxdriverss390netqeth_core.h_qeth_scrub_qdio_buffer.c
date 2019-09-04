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
struct qdio_buffer_element {int dummy; } ;
struct qdio_buffer {TYPE_1__* element; } ;
struct TYPE_2__ {scalar_t__ sflags; } ;

/* Variables and functions */
 int /*<<< orphan*/  memset (TYPE_1__*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static inline void qeth_scrub_qdio_buffer(struct qdio_buffer *buf,
					  unsigned int elements)
{
	unsigned int i;

	for (i = 0; i < elements; i++)
		memset(&buf->element[i], 0, sizeof(struct qdio_buffer_element));
	buf->element[14].sflags = 0;
	buf->element[15].sflags = 0;
}