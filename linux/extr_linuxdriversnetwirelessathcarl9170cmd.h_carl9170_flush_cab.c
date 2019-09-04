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
struct ar9170 {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  CARL9170_BCN_CTRL_DRAIN ; 
 int carl9170_bcn_ctrl (struct ar9170*,unsigned int const,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline int carl9170_flush_cab(struct ar9170 *ar,
				     const unsigned int vif_id)
{
	return carl9170_bcn_ctrl(ar, vif_id, CARL9170_BCN_CTRL_DRAIN, 0, 0);
}