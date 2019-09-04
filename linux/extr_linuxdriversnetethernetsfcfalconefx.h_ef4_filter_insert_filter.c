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
struct ef4_nic {TYPE_1__* type; } ;
struct ef4_filter_spec {int dummy; } ;
typedef  int /*<<< orphan*/  s32 ;
struct TYPE_2__ {int /*<<< orphan*/  (* filter_insert ) (struct ef4_nic*,struct ef4_filter_spec*,int) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  stub1 (struct ef4_nic*,struct ef4_filter_spec*,int) ; 

__attribute__((used)) static inline s32 ef4_filter_insert_filter(struct ef4_nic *efx,
					   struct ef4_filter_spec *spec,
					   bool replace_equal)
{
	return efx->type->filter_insert(efx, spec, replace_equal);
}