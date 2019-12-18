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
struct mtd_partition {int dummy; } ;
struct mtd_part_parser_data {int dummy; } ;
struct mtd_info {int dummy; } ;

/* Variables and functions */
 int __mtdsplit_parse_uimage (struct mtd_info*,struct mtd_partition const**,struct mtd_part_parser_data*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  uimage_find_fonfxc ; 

__attribute__((used)) static int
mtdsplit_uimage_parse_fonfxc(struct mtd_info *master,
			      const struct mtd_partition **pparts,
			      struct mtd_part_parser_data *data)
{
	return __mtdsplit_parse_uimage(master, pparts, data,
				       uimage_find_fonfxc);
}