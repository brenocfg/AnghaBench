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
struct seq_file {int dummy; } ;
struct nf_conn_counter {int /*<<< orphan*/  bytes; int /*<<< orphan*/  packets; } ;
struct nf_conn_acct {struct nf_conn_counter* counter; } ;
struct nf_conn {int dummy; } ;

/* Variables and functions */
 scalar_t__ atomic64_read (int /*<<< orphan*/ *) ; 
 struct nf_conn_acct* nf_conn_acct_find (struct nf_conn const*) ; 
 int /*<<< orphan*/  seq_printf (struct seq_file*,char*,unsigned long long,unsigned long long) ; 

unsigned int
seq_print_acct(struct seq_file *s, const struct nf_conn *ct, int dir)
{
	struct nf_conn_acct *acct;
	struct nf_conn_counter *counter;

	acct = nf_conn_acct_find(ct);
	if (!acct)
		return 0;

	counter = acct->counter;
	seq_printf(s, "packets=%llu bytes=%llu ",
		   (unsigned long long)atomic64_read(&counter[dir].packets),
		   (unsigned long long)atomic64_read(&counter[dir].bytes));

	return 0;
}