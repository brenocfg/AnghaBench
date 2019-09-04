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
struct nm256_stream {int cur_period; int periods; int period_size; scalar_t__ buf; } ;
struct nm256 {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  snd_nm256_writel (struct nm256*,int,scalar_t__) ; 

__attribute__((used)) static void snd_nm256_pcm_mark(struct nm256 *chip, struct nm256_stream *s, int reg)
{
	s->cur_period++;
	s->cur_period %= s->periods;
	snd_nm256_writel(chip, reg, s->buf + s->cur_period * s->period_size);
}