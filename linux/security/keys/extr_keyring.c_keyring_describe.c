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
struct seq_file {int dummy; } ;
struct TYPE_2__ {scalar_t__ nr_leaves_on_tree; } ;
struct key {char* description; TYPE_1__ keys; } ;

/* Variables and functions */
 scalar_t__ key_is_positive (struct key const*) ; 
 int /*<<< orphan*/  seq_printf (struct seq_file*,char*,scalar_t__) ; 
 int /*<<< orphan*/  seq_puts (struct seq_file*,char*) ; 

__attribute__((used)) static void keyring_describe(const struct key *keyring, struct seq_file *m)
{
	if (keyring->description)
		seq_puts(m, keyring->description);
	else
		seq_puts(m, "[anon]");

	if (key_is_positive(keyring)) {
		if (keyring->keys.nr_leaves_on_tree != 0)
			seq_printf(m, ": %lu", keyring->keys.nr_leaves_on_tree);
		else
			seq_puts(m, ": empty");
	}
}