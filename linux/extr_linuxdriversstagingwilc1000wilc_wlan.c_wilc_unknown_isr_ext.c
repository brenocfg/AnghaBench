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
struct wilc {TYPE_1__* hif_func; } ;
struct TYPE_2__ {int /*<<< orphan*/  (* hif_clear_int_ext ) (struct wilc*,int /*<<< orphan*/ ) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  stub1 (struct wilc*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void wilc_unknown_isr_ext(struct wilc *wilc)
{
	wilc->hif_func->hif_clear_int_ext(wilc, 0);
}