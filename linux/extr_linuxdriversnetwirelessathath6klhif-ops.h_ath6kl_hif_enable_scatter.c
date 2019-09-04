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
struct ath6kl {TYPE_1__* hif_ops; } ;
struct TYPE_2__ {int (* enable_scatter ) (struct ath6kl*) ;} ;

/* Variables and functions */
 int stub1 (struct ath6kl*) ; 

__attribute__((used)) static inline int ath6kl_hif_enable_scatter(struct ath6kl *ar)
{
	return ar->hif_ops->enable_scatter(ar);
}