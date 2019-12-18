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

/* Variables and functions */
 int /*<<< orphan*/  memcpy (void*,void*,size_t) ; 

__attribute__((used)) static void intel_pt_copy_ref(void *ref_buf, size_t ref_size, size_t buf_size,
			      void *data, size_t head)
{
	if (head >= ref_size) {
		memcpy(ref_buf, data + head - ref_size, ref_size);
	} else {
		memcpy(ref_buf, data, head);
		ref_size -= head;
		memcpy(ref_buf + head, data + buf_size - ref_size, ref_size);
	}
}