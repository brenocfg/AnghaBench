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
 int /*<<< orphan*/  snd_als4k_gcr_write_addr (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline void snd_als4k_gcr_write(struct snd_sb *sb,
					 enum als4k_gcr_t reg,
					 u32 val)
{
	snd_als4k_gcr_write_addr(sb->alt_port, reg, val);
}