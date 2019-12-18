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
struct snd_korg1212 {int /*<<< orphan*/  statusRegPtr; } ;

/* Variables and functions */
 int LOCAL_DMA1_INT_ENABLE_BIT ; 
 int LOCAL_DOORBELL_INT_ENABLE_BIT ; 
 int LOCAL_INT_ENABLE_BIT ; 
 int PCI_DOORBELL_INT_ENABLE_BIT ; 
 int PCI_INT_ENABLE_BIT ; 
 int /*<<< orphan*/  writel (int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void snd_korg1212_EnableCardInterrupts(struct snd_korg1212 * korg1212)
{
	writel(PCI_INT_ENABLE_BIT            |
	       PCI_DOORBELL_INT_ENABLE_BIT   |
	       LOCAL_INT_ENABLE_BIT          |
	       LOCAL_DOORBELL_INT_ENABLE_BIT |
	       LOCAL_DMA1_INT_ENABLE_BIT,
	       korg1212->statusRegPtr);
}