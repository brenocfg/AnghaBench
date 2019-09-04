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
typedef  int /*<<< orphan*/  AS_Host ;

/* Variables and functions */
 int /*<<< orphan*/  DMAC_TXADRHI ; 
 int /*<<< orphan*/  DMAC_TXADRLO ; 
 int /*<<< orphan*/  DMAC_TXADRMD ; 
 int dmac_read (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline unsigned int dmac_address(AS_Host *host)
{
    return dmac_read(host, DMAC_TXADRHI) << 16 |
	   dmac_read(host, DMAC_TXADRMD) << 8 |
	   dmac_read(host, DMAC_TXADRLO);
}