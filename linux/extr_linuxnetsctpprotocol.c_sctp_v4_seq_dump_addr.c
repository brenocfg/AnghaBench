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
struct TYPE_2__ {int /*<<< orphan*/  sin_addr; } ;
union sctp_addr {TYPE_1__ v4; } ;
struct seq_file {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  seq_printf (struct seq_file*,char*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void sctp_v4_seq_dump_addr(struct seq_file *seq, union sctp_addr *addr)
{
	seq_printf(seq, "%pI4 ", &addr->v4.sin_addr);
}