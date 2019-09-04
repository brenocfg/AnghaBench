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
typedef  int uint32_t ;
struct kernel_lb_addr {int dummy; } ;
struct inode {int dummy; } ;
struct extent_position {scalar_t__ bh; } ;
typedef  int int8_t ;

/* Variables and functions */
 int /*<<< orphan*/  brelse (scalar_t__) ; 
 int /*<<< orphan*/  get_bh (scalar_t__) ; 
 int /*<<< orphan*/  udf_add_aext (struct inode*,struct extent_position*,struct kernel_lb_addr*,int,int) ; 
 int udf_next_aext (struct inode*,struct extent_position*,struct kernel_lb_addr*,int*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  udf_write_aext (struct inode*,struct extent_position*,struct kernel_lb_addr*,int,int) ; 

__attribute__((used)) static int8_t udf_insert_aext(struct inode *inode, struct extent_position epos,
			      struct kernel_lb_addr neloc, uint32_t nelen)
{
	struct kernel_lb_addr oeloc;
	uint32_t oelen;
	int8_t etype;

	if (epos.bh)
		get_bh(epos.bh);

	while ((etype = udf_next_aext(inode, &epos, &oeloc, &oelen, 0)) != -1) {
		udf_write_aext(inode, &epos, &neloc, nelen, 1);
		neloc = oeloc;
		nelen = (etype << 30) | oelen;
	}
	udf_add_aext(inode, &epos, &neloc, nelen, 1);
	brelse(epos.bh);

	return (nelen >> 30);
}