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
typedef  int /*<<< orphan*/  u8 ;
typedef  int /*<<< orphan*/  u32 ;
struct itcw {int /*<<< orphan*/  tcw; } ;
struct dcw {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  TCCB_MAX_SIZE ; 
 struct dcw* tccb_add_dcw (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,void*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tcw_get_tccb (int /*<<< orphan*/ ) ; 

struct dcw *itcw_add_dcw(struct itcw *itcw, u8 cmd, u8 flags, void *cd,
			 u8 cd_count, u32 count)
{
	return tccb_add_dcw(tcw_get_tccb(itcw->tcw), TCCB_MAX_SIZE, cmd,
			    flags, cd, cd_count, count);
}