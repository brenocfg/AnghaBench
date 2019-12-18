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
struct rds_connection {int /*<<< orphan*/  c_flags; } ;

/* Variables and functions */
 int /*<<< orphan*/  RDS_RECV_REFILL ; 
 scalar_t__ test_and_set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int acquire_refill(struct rds_connection *conn)
{
	return test_and_set_bit(RDS_RECV_REFILL, &conn->c_flags) == 0;
}