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
struct snd_intelhad {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  AUD_BUF_ADDR (int) ; 
 int /*<<< orphan*/  AUD_BUF_LEN (int) ; 
 int /*<<< orphan*/  had_write_register (struct snd_intelhad*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void had_invalidate_bd(struct snd_intelhad *intelhaddata,
			      int idx)
{
	had_write_register(intelhaddata, AUD_BUF_ADDR(idx), 0);
	had_write_register(intelhaddata, AUD_BUF_LEN(idx), 0);
}