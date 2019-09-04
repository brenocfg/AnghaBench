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
struct snd_sb {int dummy; } ;
typedef  enum als4k_cr_t { ____Placeholder_als4k_cr_t } als4k_cr_t ;

/* Variables and functions */
 int /*<<< orphan*/  snd_sbmixer_write (struct snd_sb*,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline void snd_als4_cr_write(struct snd_sb *chip,
					enum als4k_cr_t reg,
					u8 data)
{
	/* Control Register is reg | 0xc0 (bit 7, 6 set) on sbmixer_index
	 * NOTE: assumes chip->mixer_lock to be locked externally already!
	 * SPECS_PAGE: 6 */
	snd_sbmixer_write(chip, reg | 0xc0, data);
}