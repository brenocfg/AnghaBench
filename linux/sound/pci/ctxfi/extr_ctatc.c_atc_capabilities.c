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
struct hw {struct capabilities (* capabilities ) (struct hw*) ;} ;
struct ct_atc {struct hw* hw; } ;
struct capabilities {int dummy; } ;

/* Variables and functions */
 struct capabilities stub1 (struct hw*) ; 

__attribute__((used)) static struct capabilities atc_capabilities(struct ct_atc *atc)
{
	struct hw *hw = atc->hw;

	return hw->capabilities(hw);
}