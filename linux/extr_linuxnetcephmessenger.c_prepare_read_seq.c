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
struct ceph_connection {int /*<<< orphan*/  in_tag; scalar_t__ in_base_pos; } ;

/* Variables and functions */
 int /*<<< orphan*/  CEPH_MSGR_TAG_SEQ ; 
 int /*<<< orphan*/  dout (char*,struct ceph_connection*) ; 

__attribute__((used)) static void prepare_read_seq(struct ceph_connection *con)
{
	dout("prepare_read_seq %p\n", con);
	con->in_base_pos = 0;
	con->in_tag = CEPH_MSGR_TAG_SEQ;
}