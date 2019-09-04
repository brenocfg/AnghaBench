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
struct symbol {int dummy; } ;
typedef  void annotation ;
struct TYPE_2__ {int priv_size; } ;

/* Variables and functions */
 TYPE_1__ symbol_conf ; 

__attribute__((used)) static inline struct annotation *symbol__annotation(struct symbol *sym)
{
	return (void *)sym - symbol_conf.priv_size;
}