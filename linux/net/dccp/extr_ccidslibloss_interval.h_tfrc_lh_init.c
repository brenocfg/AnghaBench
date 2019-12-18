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
struct tfrc_loss_hist {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  memset (struct tfrc_loss_hist*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static inline void tfrc_lh_init(struct tfrc_loss_hist *lh)
{
	memset(lh, 0, sizeof(struct tfrc_loss_hist));
}