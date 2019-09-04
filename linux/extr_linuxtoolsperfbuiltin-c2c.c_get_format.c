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
struct perf_hpp_fmt {void* collapse; int /*<<< orphan*/  free; int /*<<< orphan*/  equal; int /*<<< orphan*/  width; int /*<<< orphan*/  header; int /*<<< orphan*/  entry; int /*<<< orphan*/ * color; void* sort; void* cmp; int /*<<< orphan*/  sort_list; int /*<<< orphan*/  list; } ;
struct c2c_fmt {struct perf_hpp_fmt fmt; struct c2c_dimension* dim; } ;
struct c2c_dimension {void* cmp; scalar_t__ se; int /*<<< orphan*/  entry; int /*<<< orphan*/ * color; } ;

/* Variables and functions */
 int /*<<< orphan*/  INIT_LIST_HEAD (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  c2c_header ; 
 void* c2c_se_cmp ; 
 void* c2c_se_collapse ; 
 int /*<<< orphan*/  c2c_se_entry ; 
 int /*<<< orphan*/  c2c_width ; 
 int /*<<< orphan*/  fmt_equal ; 
 int /*<<< orphan*/  fmt_free ; 
 struct c2c_dimension* get_dimension (char const*) ; 
 struct c2c_fmt* zalloc (int) ; 

__attribute__((used)) static struct c2c_fmt *get_format(const char *name)
{
	struct c2c_dimension *dim = get_dimension(name);
	struct c2c_fmt *c2c_fmt;
	struct perf_hpp_fmt *fmt;

	if (!dim)
		return NULL;

	c2c_fmt = zalloc(sizeof(*c2c_fmt));
	if (!c2c_fmt)
		return NULL;

	c2c_fmt->dim = dim;

	fmt = &c2c_fmt->fmt;
	INIT_LIST_HEAD(&fmt->list);
	INIT_LIST_HEAD(&fmt->sort_list);

	fmt->cmp	= dim->se ? c2c_se_cmp   : dim->cmp;
	fmt->sort	= dim->se ? c2c_se_cmp   : dim->cmp;
	fmt->color	= dim->se ? NULL	 : dim->color;
	fmt->entry	= dim->se ? c2c_se_entry : dim->entry;
	fmt->header	= c2c_header;
	fmt->width	= c2c_width;
	fmt->collapse	= dim->se ? c2c_se_collapse : dim->cmp;
	fmt->equal	= fmt_equal;
	fmt->free	= fmt_free;

	return c2c_fmt;
}