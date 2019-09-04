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
struct c67x00_sie {int /*<<< orphan*/  sie_num; struct c67x00_device* dev; } ;
struct c67x00_lcp_int_data {int dummy; } ;
struct c67x00_device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int) ; 
 int /*<<< orphan*/  HUSB_SIE_INIT_INT (int /*<<< orphan*/ ) ; 
 int c67x00_comm_exec_int (struct c67x00_device*,int /*<<< orphan*/ ,struct c67x00_lcp_int_data*) ; 

__attribute__((used)) static inline void c67x00_ll_husb_sie_init(struct c67x00_sie *sie)
{
	struct c67x00_device *dev = sie->dev;
	struct c67x00_lcp_int_data data;
	int rc;

	rc = c67x00_comm_exec_int(dev, HUSB_SIE_INIT_INT(sie->sie_num), &data);
	BUG_ON(rc); /* No return path for error code; crash spectacularly */
}