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
struct nfs4_sequence_res {int sr_status; scalar_t__ sr_status_flags; int /*<<< orphan*/  sr_timestamp; } ;

/* Variables and functions */
 int /*<<< orphan*/  jiffies ; 

__attribute__((used)) static void nfs41_sequence_res_init(struct nfs4_sequence_res *res)
{
	res->sr_timestamp = jiffies;
	res->sr_status_flags = 0;
	res->sr_status = 1;
}