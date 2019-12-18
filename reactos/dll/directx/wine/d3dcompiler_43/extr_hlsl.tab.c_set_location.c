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
struct source_location {int /*<<< orphan*/  col; int /*<<< orphan*/  line; int /*<<< orphan*/  file; } ;
struct YYLTYPE {int /*<<< orphan*/  first_column; int /*<<< orphan*/  first_line; } ;
struct TYPE_2__ {int /*<<< orphan*/  source_file; } ;

/* Variables and functions */
 TYPE_1__ hlsl_ctx ; 

__attribute__((used)) static void set_location(struct source_location *loc, const struct YYLTYPE *l)
{
    loc->file = hlsl_ctx.source_file;
    loc->line = l->first_line;
    loc->col = l->first_column;
}