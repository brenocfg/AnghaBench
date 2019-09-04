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
struct nm256 {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  NM_RECORD_ENABLE_REG ; 
 int /*<<< orphan*/  snd_nm256_writeb (struct nm256*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
snd_nm256_capture_stop(struct nm256 *chip)
{
	/* Disable recording engine. */
	snd_nm256_writeb(chip, NM_RECORD_ENABLE_REG, 0);
}