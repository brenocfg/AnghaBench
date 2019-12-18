#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ u32 ;
struct seq_file {int dummy; } ;
struct rdmacg_resource_pool {TYPE_1__* resources; } ;
typedef  enum rdmacg_file_type { ____Placeholder_rdmacg_file_type } rdmacg_file_type ;
struct TYPE_4__ {int private; } ;
struct TYPE_3__ {scalar_t__ max; scalar_t__ usage; } ;

/* Variables and functions */
 int /*<<< orphan*/  RDMACG_MAX_STR ; 
 int RDMACG_RESOURCE_MAX ; 
 int RDMACG_RESOURCE_TYPE_MAX ; 
 scalar_t__ S32_MAX ; 
 int /*<<< orphan*/ * rdmacg_resource_names ; 
 TYPE_2__* seq_cft (struct seq_file*) ; 
 int /*<<< orphan*/  seq_printf (struct seq_file*,char*,scalar_t__) ; 
 int /*<<< orphan*/  seq_putc (struct seq_file*,char) ; 
 int /*<<< orphan*/  seq_puts (struct seq_file*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void print_rpool_values(struct seq_file *sf,
			       struct rdmacg_resource_pool *rpool)
{
	enum rdmacg_file_type sf_type;
	int i;
	u32 value;

	sf_type = seq_cft(sf)->private;

	for (i = 0; i < RDMACG_RESOURCE_MAX; i++) {
		seq_puts(sf, rdmacg_resource_names[i]);
		seq_putc(sf, '=');
		if (sf_type == RDMACG_RESOURCE_TYPE_MAX) {
			if (rpool)
				value = rpool->resources[i].max;
			else
				value = S32_MAX;
		} else {
			if (rpool)
				value = rpool->resources[i].usage;
			else
				value = 0;
		}

		if (value == S32_MAX)
			seq_puts(sf, RDMACG_MAX_STR);
		else
			seq_printf(sf, "%d", value);
		seq_putc(sf, ' ');
	}
}