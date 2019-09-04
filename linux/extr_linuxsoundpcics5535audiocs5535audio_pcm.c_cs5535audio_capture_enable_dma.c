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
struct cs5535audio {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  ACC_BM1_CMD ; 
 int /*<<< orphan*/  BM_CTL_EN ; 
 int /*<<< orphan*/  cs_writeb (struct cs5535audio*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void cs5535audio_capture_enable_dma(struct cs5535audio *cs5535au)
{
	cs_writeb(cs5535au, ACC_BM1_CMD, BM_CTL_EN);
}