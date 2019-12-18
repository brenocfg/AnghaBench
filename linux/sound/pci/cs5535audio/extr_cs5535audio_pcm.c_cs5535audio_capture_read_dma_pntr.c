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
typedef  int /*<<< orphan*/  u32 ;
struct cs5535audio {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  ACC_BM1_PNTR ; 
 int /*<<< orphan*/  cs_readl (struct cs5535audio*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static u32 cs5535audio_capture_read_dma_pntr(struct cs5535audio *cs5535au)
{
	return cs_readl(cs5535au, ACC_BM1_PNTR);
}