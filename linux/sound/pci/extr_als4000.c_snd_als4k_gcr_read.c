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
struct snd_sb {int /*<<< orphan*/  alt_port; } ;
typedef  enum als4k_gcr_t { ____Placeholder_als4k_gcr_t } als4k_gcr_t ;

/* Variables and functions */
 int /*<<< orphan*/  snd_als4k_gcr_read_addr (int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static inline u32 snd_als4k_gcr_read(struct snd_sb *sb, enum als4k_gcr_t reg)
{
	return snd_als4k_gcr_read_addr(sb->alt_port, reg);
}