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
struct gport {int dummy; } ;
typedef  int /*<<< orphan*/  RBuffer ;

/* Variables and functions */
 int /*<<< orphan*/ * r_buf_data (int /*<<< orphan*/ *,scalar_t__*) ; 
 scalar_t__ sp_blocking_write (struct gport*,int /*<<< orphan*/  const*,scalar_t__,int) ; 
 int /*<<< orphan*/  sp_flush (struct gport*) ; 

__attribute__((used)) static int gprobe_send_request_sp(struct gport *port, RBuffer *request) {
	sp_flush (port);

	ut64 tmpsz;
	const ut8 *tmp = r_buf_data (request, &tmpsz);
	if (sp_blocking_write (port, tmp, tmpsz, 100) != tmpsz) {
		return -1;
	}

	return 0;
}