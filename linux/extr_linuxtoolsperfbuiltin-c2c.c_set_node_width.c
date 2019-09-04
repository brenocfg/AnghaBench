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
struct c2c_hist_entry {int /*<<< orphan*/ * hists; } ;
struct c2c_dimension {int width; } ;
struct TYPE_2__ {int /*<<< orphan*/  hists; } ;

/* Variables and functions */
 TYPE_1__ c2c ; 
 struct c2c_dimension dim_dcacheline_node ; 
 struct c2c_dimension dim_offset_node ; 

__attribute__((used)) static void set_node_width(struct c2c_hist_entry *c2c_he, int len)
{
	struct c2c_dimension *dim;

	dim = &c2c.hists == c2c_he->hists ?
	      &dim_dcacheline_node : &dim_offset_node;

	if (len > dim->width)
		dim->width = len;
}