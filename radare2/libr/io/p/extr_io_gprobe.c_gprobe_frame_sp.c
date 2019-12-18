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
typedef  scalar_t__ ut64 ;
typedef  int /*<<< orphan*/  RBuffer ;

/* Variables and functions */
 int /*<<< orphan*/  gprobe_checksum (int /*<<< orphan*/  const*,scalar_t__) ; 
 int /*<<< orphan*/  r_buf_append_bytes (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/ * r_buf_data (int /*<<< orphan*/ *,scalar_t__*) ; 
 int /*<<< orphan*/  r_buf_prepend_bytes (int /*<<< orphan*/ *,int /*<<< orphan*/  const*,int) ; 

__attribute__((used)) static void gprobe_frame_sp(RBuffer *frame) {
	ut64 size;
	const ut8 *tmp = r_buf_data (frame, &size);
	size += 2;
	ut8 checksum;

	r_buf_prepend_bytes (frame, (const ut8 *)&size, 1);
	checksum = gprobe_checksum (tmp, size - 1);

	r_buf_append_bytes (frame, &checksum, 1);
}