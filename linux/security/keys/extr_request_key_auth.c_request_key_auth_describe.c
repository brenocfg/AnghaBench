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
struct request_key_auth {int /*<<< orphan*/  callout_len; int /*<<< orphan*/  pid; } ;
struct key {char* description; } ;

/* Variables and functions */
 struct request_key_auth* dereference_key_rcu (struct key const*) ; 
 scalar_t__ key_is_positive (struct key const*) ; 
 int /*<<< orphan*/  seq_printf (struct seq_file*,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  seq_puts (struct seq_file*,char*) ; 

__attribute__((used)) static void request_key_auth_describe(const struct key *key,
				      struct seq_file *m)
{
	struct request_key_auth *rka = dereference_key_rcu(key);

	if (!rka)
		return;

	seq_puts(m, "key:");
	seq_puts(m, key->description);
	if (key_is_positive(key))
		seq_printf(m, " pid:%d ci:%zu", rka->pid, rka->callout_len);
}