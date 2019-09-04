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
struct TYPE_2__ {int /*<<< orphan*/ * data; } ;
struct key {int datalen; TYPE_1__ payload; int /*<<< orphan*/  description; } ;

/* Variables and functions */
 int PTR_ERR (int /*<<< orphan*/ ) ; 
 size_t dns_key_error ; 
 scalar_t__ key_is_positive (struct key const*) ; 
 int /*<<< orphan*/  seq_printf (struct seq_file*,char*,int) ; 
 int /*<<< orphan*/  seq_puts (struct seq_file*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void dns_resolver_describe(const struct key *key, struct seq_file *m)
{
	seq_puts(m, key->description);
	if (key_is_positive(key)) {
		int err = PTR_ERR(key->payload.data[dns_key_error]);

		if (err)
			seq_printf(m, ": %d", err);
		else
			seq_printf(m, ": %u", key->datalen);
	}
}