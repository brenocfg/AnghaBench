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
struct key {int /*<<< orphan*/  datalen; int /*<<< orphan*/  description; } ;

/* Variables and functions */
 scalar_t__ key_is_positive (struct key const*) ; 
 int /*<<< orphan*/  seq_printf (struct seq_file*,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  seq_puts (struct seq_file*,int /*<<< orphan*/ ) ; 

void user_describe(const struct key *key, struct seq_file *m)
{
	seq_puts(m, key->description);
	if (key_is_positive(key))
		seq_printf(m, ": %u", key->datalen);
}