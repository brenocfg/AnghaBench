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
struct hif_scatter_req {int dummy; } ;
struct ath6kl {TYPE_1__* hif_ops; } ;
struct TYPE_2__ {void (* scatter_req_add ) (struct ath6kl*,struct hif_scatter_req*) ;} ;

/* Variables and functions */
 void stub1 (struct ath6kl*,struct hif_scatter_req*) ; 

__attribute__((used)) static inline void hif_scatter_req_add(struct ath6kl *ar,
				       struct hif_scatter_req *s_req)
{
	return ar->hif_ops->scatter_req_add(ar, s_req);
}