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
typedef  int /*<<< orphan*/  u16 ;
struct qbman_swp {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  CODE_CDAN_WE_EN ; 
 int qbman_swp_CDAN_set (struct qbman_swp*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline int qbman_swp_CDAN_enable(struct qbman_swp *s, u16 channelid)
{
	return qbman_swp_CDAN_set(s, channelid,
				  CODE_CDAN_WE_EN,
				  1, 0);
}