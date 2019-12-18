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
typedef  int /*<<< orphan*/  zend_shared_segment ;

/* Variables and functions */
 int /*<<< orphan*/  memcpy (void*,void*,int) ; 

__attribute__((used)) static void copy_shared_segments(void *to, void *from, int count, int size)
{
	zend_shared_segment **shared_segments_v = (zend_shared_segment **)to;
	void *shared_segments_to_p = ((char *)to + count*(sizeof(void *)));
	void *shared_segments_from_p = from;
	int i;

	for (i = 0; i < count; i++) {
		shared_segments_v[i] = 	shared_segments_to_p;
		memcpy(shared_segments_to_p, shared_segments_from_p, size);
		shared_segments_to_p = ((char *)shared_segments_to_p + size);
		shared_segments_from_p = ((char *)shared_segments_from_p + size);
	}
}