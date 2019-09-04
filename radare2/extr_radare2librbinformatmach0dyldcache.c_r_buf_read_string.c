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
typedef  scalar_t__ ut8 ;
typedef  int /*<<< orphan*/  ut64 ;
typedef  int /*<<< orphan*/  RBuffer ;

/* Variables and functions */
 scalar_t__* malloc (int) ; 
 int /*<<< orphan*/  r_buf_read_at (int /*<<< orphan*/ *,int /*<<< orphan*/ ,scalar_t__*,int) ; 

__attribute__((used)) static char *r_buf_read_string(RBuffer *buf, ut64 addr, int len) {
	ut8 *data = malloc (len);
	if (data) {
		r_buf_read_at (buf, addr, data, len);
		data[len - 1] = 0;
		return (char *)data;
	}
	return NULL;
}