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
struct annotation {int dummy; } ;
struct TYPE_2__ {int init_annotation; int priv_size; scalar_t__ initialized; } ;

/* Variables and functions */
 int /*<<< orphan*/  pr_err (char*) ; 
 TYPE_1__ symbol_conf ; 

int symbol__annotation_init(void)
{
	if (symbol_conf.init_annotation)
		return 0;

	if (symbol_conf.initialized) {
		pr_err("Annotation needs to be init before symbol__init()\n");
		return -1;
	}

	symbol_conf.priv_size += sizeof(struct annotation);
	symbol_conf.init_annotation = true;
	return 0;
}