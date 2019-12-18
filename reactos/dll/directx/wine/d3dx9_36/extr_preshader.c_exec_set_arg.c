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
struct d3dx_regstore {int dummy; } ;
struct d3dx_pres_reg {scalar_t__ offset; int /*<<< orphan*/  table; } ;

/* Variables and functions */
 int /*<<< orphan*/  regstore_set_double (struct d3dx_regstore*,int /*<<< orphan*/ ,scalar_t__,double) ; 

__attribute__((used)) static void exec_set_arg(struct d3dx_regstore *rs, const struct d3dx_pres_reg *reg,
        unsigned int comp, double res)
{
    regstore_set_double(rs, reg->table, reg->offset + comp, res);
}