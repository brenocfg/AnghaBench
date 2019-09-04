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
typedef  int u64 ;
struct ntb_dev {int dummy; } ;
struct intel_ntb_dev {int db_vec_count; int db_valid_mask; } ;

/* Variables and functions */
 int ndev_vec_mask (struct intel_ntb_dev*,int) ; 
 struct intel_ntb_dev* ntb_ndev (struct ntb_dev*) ; 

u64 intel_ntb_db_vector_mask(struct ntb_dev *ntb, int db_vector)
{
	struct intel_ntb_dev *ndev = ntb_ndev(ntb);

	if (db_vector < 0 || db_vector > ndev->db_vec_count)
		return 0;

	return ndev->db_valid_mask & ndev_vec_mask(ndev, db_vector);
}