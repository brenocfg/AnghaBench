#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct napi_struct {scalar_t__ dev; } ;
struct TYPE_2__ {scalar_t__ vlddes; } ;

/* Variables and functions */
 int ARRAY_SIZE (scalar_t__*) ; 
 int /*<<< orphan*/  IFX_REG_W32_MASK (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MBOX_IGU1_IER ; 
 int /*<<< orphan*/  MBOX_IGU1_ISRC ; 
 TYPE_1__* WRX_DMA_CHANNEL_CONFIG (int) ; 
 scalar_t__* g_net_dev ; 
 int /*<<< orphan*/  napi_complete (struct napi_struct*) ; 
 int /*<<< orphan*/  netif_running (scalar_t__) ; 
 unsigned int ptm_poll (int,int) ; 

__attribute__((used)) static int ptm_napi_poll(struct napi_struct *napi, int budget)
{
    int ndev;
    unsigned int work_done;

    for ( ndev = 0; ndev < ARRAY_SIZE(g_net_dev) && g_net_dev[ndev] != napi->dev; ndev++ );

    work_done = ptm_poll(ndev, budget);

    //  interface down
    if ( !netif_running(napi->dev) ) {
        napi_complete(napi);
        return work_done;
    }

    //  no more traffic
    if ( WRX_DMA_CHANNEL_CONFIG(ndev)->vlddes == 0 ) {
        //  clear interrupt
        IFX_REG_W32_MASK(0, 1 << ndev, MBOX_IGU1_ISRC);
        //  double check
        if ( WRX_DMA_CHANNEL_CONFIG(ndev)->vlddes == 0 ) {
            napi_complete(napi);
            IFX_REG_W32_MASK(0, 1 << ndev, MBOX_IGU1_IER);
            return work_done;
        }
    }

    //  next round
    return work_done;
}