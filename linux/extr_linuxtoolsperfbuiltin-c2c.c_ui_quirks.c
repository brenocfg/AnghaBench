#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_22__   TYPE_9__ ;
typedef  struct TYPE_21__   TYPE_8__ ;
typedef  struct TYPE_20__   TYPE_7__ ;
typedef  struct TYPE_19__   TYPE_6__ ;
typedef  struct TYPE_18__   TYPE_5__ ;
typedef  struct TYPE_17__   TYPE_4__ ;
typedef  struct TYPE_16__   TYPE_3__ ;
typedef  struct TYPE_15__   TYPE_2__ ;
typedef  struct TYPE_14__   TYPE_1__ ;
typedef  struct TYPE_13__   TYPE_11__ ;
typedef  struct TYPE_12__   TYPE_10__ ;

/* Type definitions */
struct TYPE_22__ {scalar_t__ width; } ;
struct TYPE_21__ {scalar_t__ width; } ;
struct TYPE_17__ {TYPE_3__* line; } ;
struct TYPE_20__ {int width; TYPE_4__ header; } ;
struct TYPE_19__ {scalar_t__ width; } ;
struct TYPE_18__ {int /*<<< orphan*/  header; } ;
struct TYPE_16__ {char* text; } ;
struct TYPE_15__ {TYPE_1__* line; } ;
struct TYPE_14__ {char* text; } ;
struct TYPE_13__ {size_t display; int /*<<< orphan*/  use_stdio; } ;
struct TYPE_12__ {TYPE_2__ header; scalar_t__ width; } ;

/* Variables and functions */
 int ENOMEM ; 
 TYPE_11__ c2c ; 
 TYPE_10__ dim_dcacheline ; 
 TYPE_9__ dim_dcacheline_count ; 
 TYPE_8__ dim_dcacheline_node ; 
 TYPE_7__ dim_offset ; 
 TYPE_6__ dim_offset_node ; 
 TYPE_5__ dim_percent_hitm ; 
 char* fill_line (char const*,scalar_t__) ; 
 TYPE_4__ header_offset_tui ; 
 int /*<<< orphan*/ * percent_hitm_header ; 

__attribute__((used)) static int ui_quirks(void)
{
	const char *nodestr = "Data address";
	char *buf;

	if (!c2c.use_stdio) {
		dim_offset.width  = 5;
		dim_offset.header = header_offset_tui;
		nodestr = "CL";
	}

	dim_percent_hitm.header = percent_hitm_header[c2c.display];

	/* Fix the zero line for dcacheline column. */
	buf = fill_line("Cacheline", dim_dcacheline.width +
				     dim_dcacheline_node.width +
				     dim_dcacheline_count.width + 4);
	if (!buf)
		return -ENOMEM;

	dim_dcacheline.header.line[0].text = buf;

	/* Fix the zero line for offset column. */
	buf = fill_line(nodestr, dim_offset.width +
			         dim_offset_node.width +
				 dim_dcacheline_count.width + 4);
	if (!buf)
		return -ENOMEM;

	dim_offset.header.line[0].text = buf;

	return 0;
}