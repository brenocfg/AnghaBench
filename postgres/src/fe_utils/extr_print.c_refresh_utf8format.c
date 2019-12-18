#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_16__   TYPE_7__ ;
typedef  struct TYPE_15__   TYPE_6__ ;
typedef  struct TYPE_14__   TYPE_5__ ;
typedef  struct TYPE_13__   TYPE_4__ ;
typedef  struct TYPE_12__   TYPE_3__ ;
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
struct TYPE_11__ {char* horizontal; int /*<<< orphan*/ * vertical_and_left; int /*<<< orphan*/ * vertical_and_right; } ;
typedef  TYPE_2__ unicodeStyleRowFormat ;
struct TYPE_12__ {int /*<<< orphan*/  vertical; int /*<<< orphan*/ * up_and_horizontal; int /*<<< orphan*/ * vertical_and_horizontal; int /*<<< orphan*/ * down_and_horizontal; } ;
typedef  TYPE_3__ unicodeStyleColumnFormat ;
struct TYPE_13__ {char* horizontal; int /*<<< orphan*/  vertical; int /*<<< orphan*/  left_and_right; int /*<<< orphan*/  up_and_right; int /*<<< orphan*/  down_and_left; int /*<<< orphan*/  down_and_right; } ;
typedef  TYPE_4__ unicodeStyleBorderFormat ;
struct TYPE_14__ {char* name; int /*<<< orphan*/  wrap_right_border; int /*<<< orphan*/  wrap_right; int /*<<< orphan*/  wrap_left; int /*<<< orphan*/  nl_right; int /*<<< orphan*/  nl_left; int /*<<< orphan*/  header_nl_right; int /*<<< orphan*/  header_nl_left; int /*<<< orphan*/  midvrule_blank; int /*<<< orphan*/  midvrule_wrap; int /*<<< orphan*/  midvrule_nl; TYPE_1__* lrule; } ;
typedef  TYPE_5__ printTextFormat ;
struct TYPE_15__ {size_t unicode_border_linestyle; size_t unicode_header_linestyle; size_t unicode_column_linestyle; } ;
typedef  TYPE_6__ printTableOpt ;
struct TYPE_16__ {int /*<<< orphan*/  wrap_right_border; int /*<<< orphan*/  wrap_right; int /*<<< orphan*/  wrap_left; int /*<<< orphan*/  nl_right; int /*<<< orphan*/  nl_left; int /*<<< orphan*/  header_nl_right; int /*<<< orphan*/  header_nl_left; TYPE_3__* column_style; TYPE_2__* row_style; TYPE_4__* border_style; } ;
struct TYPE_10__ {char* hrule; int /*<<< orphan*/  rightvrule; int /*<<< orphan*/  midvrule; int /*<<< orphan*/  leftvrule; } ;

/* Variables and functions */
 size_t PRINT_RULE_BOTTOM ; 
 size_t PRINT_RULE_DATA ; 
 size_t PRINT_RULE_MIDDLE ; 
 size_t PRINT_RULE_TOP ; 
 TYPE_5__ pg_utf8format ; 
 TYPE_7__ unicode_style ; 

void
refresh_utf8format(const printTableOpt *opt)
{
	printTextFormat *popt = &pg_utf8format;

	const unicodeStyleBorderFormat *border;
	const unicodeStyleRowFormat *header;
	const unicodeStyleColumnFormat *column;

	popt->name = "unicode";

	border = &unicode_style.border_style[opt->unicode_border_linestyle];
	header = &unicode_style.row_style[opt->unicode_header_linestyle];
	column = &unicode_style.column_style[opt->unicode_column_linestyle];

	popt->lrule[PRINT_RULE_TOP].hrule = border->horizontal;
	popt->lrule[PRINT_RULE_TOP].leftvrule = border->down_and_right;
	popt->lrule[PRINT_RULE_TOP].midvrule = column->down_and_horizontal[opt->unicode_border_linestyle];
	popt->lrule[PRINT_RULE_TOP].rightvrule = border->down_and_left;

	popt->lrule[PRINT_RULE_MIDDLE].hrule = header->horizontal;
	popt->lrule[PRINT_RULE_MIDDLE].leftvrule = header->vertical_and_right[opt->unicode_border_linestyle];
	popt->lrule[PRINT_RULE_MIDDLE].midvrule = column->vertical_and_horizontal[opt->unicode_header_linestyle];
	popt->lrule[PRINT_RULE_MIDDLE].rightvrule = header->vertical_and_left[opt->unicode_border_linestyle];

	popt->lrule[PRINT_RULE_BOTTOM].hrule = border->horizontal;
	popt->lrule[PRINT_RULE_BOTTOM].leftvrule = border->up_and_right;
	popt->lrule[PRINT_RULE_BOTTOM].midvrule = column->up_and_horizontal[opt->unicode_border_linestyle];
	popt->lrule[PRINT_RULE_BOTTOM].rightvrule = border->left_and_right;

	/* N/A */
	popt->lrule[PRINT_RULE_DATA].hrule = "";
	popt->lrule[PRINT_RULE_DATA].leftvrule = border->vertical;
	popt->lrule[PRINT_RULE_DATA].midvrule = column->vertical;
	popt->lrule[PRINT_RULE_DATA].rightvrule = border->vertical;

	popt->midvrule_nl = column->vertical;
	popt->midvrule_wrap = column->vertical;
	popt->midvrule_blank = column->vertical;

	/* Same for all unicode today */
	popt->header_nl_left = unicode_style.header_nl_left;
	popt->header_nl_right = unicode_style.header_nl_right;
	popt->nl_left = unicode_style.nl_left;
	popt->nl_right = unicode_style.nl_right;
	popt->wrap_left = unicode_style.wrap_left;
	popt->wrap_right = unicode_style.wrap_right;
	popt->wrap_right_border = unicode_style.wrap_right_border;

	return;
}