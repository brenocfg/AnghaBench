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
struct TYPE_3__ {int /*<<< orphan*/  n_functions; } ;
typedef  TYPE_1__ idasig_v6_v7_t ;
typedef  int /*<<< orphan*/  RBuffer ;

/* Variables and functions */
 int r_buf_read (int /*<<< orphan*/ *,unsigned char*,int) ; 

__attribute__((used)) static int parse_v6_v7_header(RBuffer *buf, idasig_v6_v7_t *header) {
	if (r_buf_read (buf, (unsigned char *)&header->n_functions, sizeof (header->n_functions)) != sizeof (header->n_functions)) {
		return false;
	}

	return true;
}