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
struct pcm3168a_priv {int /*<<< orphan*/  regmap; int /*<<< orphan*/  sysclk; } ;

/* Variables and functions */
 int /*<<< orphan*/  DIV_ROUND_UP (int,int /*<<< orphan*/ ) ; 
 int PCM3168A_MRST_MASK ; 
 int /*<<< orphan*/  PCM3168A_RST_SMODE ; 
 int PCM3168A_SRST_MASK ; 
 int /*<<< orphan*/  msleep (int /*<<< orphan*/ ) ; 
 int regmap_write (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int pcm3168a_reset(struct pcm3168a_priv *pcm3168a)
{
	int ret;

	ret = regmap_write(pcm3168a->regmap, PCM3168A_RST_SMODE, 0);
	if (ret)
		return ret;

	/* Internal reset is de-asserted after 3846 SCKI cycles */
	msleep(DIV_ROUND_UP(3846 * 1000, pcm3168a->sysclk));

	return regmap_write(pcm3168a->regmap, PCM3168A_RST_SMODE,
			PCM3168A_MRST_MASK | PCM3168A_SRST_MASK);
}