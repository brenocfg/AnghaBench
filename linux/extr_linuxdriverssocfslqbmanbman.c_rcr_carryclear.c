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
struct bm_rcr_entry {int dummy; } ;

/* Variables and functions */
 uintptr_t RCR_CARRY ; 

__attribute__((used)) static struct bm_rcr_entry *rcr_carryclear(struct bm_rcr_entry *p)
{
	uintptr_t addr = (uintptr_t)p;

	addr &= ~RCR_CARRY;

	return (struct bm_rcr_entry *)addr;
}