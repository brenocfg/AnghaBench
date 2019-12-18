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
struct amd7930_map {int gx; int gr; int stgr; int ger; int mmr1; int mmr2; } ;
struct snd_amd7930 {scalar_t__ regs; struct amd7930_map map; } ;

/* Variables and functions */
 scalar_t__ AMD7930_CR ; 
 scalar_t__ AMD7930_DR ; 
 int AMR_MAP_GER ; 
 int AMR_MAP_GR ; 
 int AMR_MAP_GX ; 
 int AMR_MAP_MMR1 ; 
 int AMR_MAP_MMR2 ; 
 int AMR_MAP_STGR ; 
 int /*<<< orphan*/  sbus_writeb (int,scalar_t__) ; 

__attribute__((used)) static void __amd7930_write_map(struct snd_amd7930 *amd)
{
	struct amd7930_map *map = &amd->map;

	sbus_writeb(AMR_MAP_GX, amd->regs + AMD7930_CR);
	sbus_writeb(((map->gx >> 0) & 0xff), amd->regs + AMD7930_DR);
	sbus_writeb(((map->gx >> 8) & 0xff), amd->regs + AMD7930_DR);

	sbus_writeb(AMR_MAP_GR, amd->regs + AMD7930_CR);
	sbus_writeb(((map->gr >> 0) & 0xff), amd->regs + AMD7930_DR);
	sbus_writeb(((map->gr >> 8) & 0xff), amd->regs + AMD7930_DR);

	sbus_writeb(AMR_MAP_STGR, amd->regs + AMD7930_CR);
	sbus_writeb(((map->stgr >> 0) & 0xff), amd->regs + AMD7930_DR);
	sbus_writeb(((map->stgr >> 8) & 0xff), amd->regs + AMD7930_DR);

	sbus_writeb(AMR_MAP_GER, amd->regs + AMD7930_CR);
	sbus_writeb(((map->ger >> 0) & 0xff), amd->regs + AMD7930_DR);
	sbus_writeb(((map->ger >> 8) & 0xff), amd->regs + AMD7930_DR);

	sbus_writeb(AMR_MAP_MMR1, amd->regs + AMD7930_CR);
	sbus_writeb(map->mmr1, amd->regs + AMD7930_DR);

	sbus_writeb(AMR_MAP_MMR2, amd->regs + AMD7930_CR);
	sbus_writeb(map->mmr2, amd->regs + AMD7930_DR);
}