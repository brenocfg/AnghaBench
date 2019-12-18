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
struct parser {int dummy; } ;
struct TYPE_2__ {int ival; } ;
struct expr {TYPE_1__ u; int /*<<< orphan*/  type; } ;

/* Variables and functions */
 int /*<<< orphan*/  EXPR_BVAL ; 
 struct expr* alloc_mem (struct parser*,int) ; 

__attribute__((used)) static struct expr *expr_bval( struct parser *parser, int val )
{
    struct expr *e = alloc_mem( parser, sizeof *e );
    if (e)
    {
        e->type = EXPR_BVAL;
        e->u.ival = val;
    }
    return e;
}