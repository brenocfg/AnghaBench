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
struct napi_struct {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  IFX_REG_W32_MASK (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MBOX_IGU1_IER ; 
 int /*<<< orphan*/  MBOX_IGU1_ISRC ; 
 int /*<<< orphan*/  napi_complete (struct napi_struct*) ; 
 int /*<<< orphan*/  netif_running (int /*<<< orphan*/ ) ; 
 unsigned int ptm_poll (int,int) ; 

__attribute__((used)) static int ptm_napi_poll(struct napi_struct *napi, int budget)
{
    int ndev = 0;
    unsigned int work_done;

    work_done = ptm_poll(ndev, budget);

    //  interface down
    if ( !netif_running(napi->dev) ) {
        napi_complete(napi);
        return work_done;
    }

    //  clear interrupt
    IFX_REG_W32_MASK(0, 1, MBOX_IGU1_ISRC);
    //  no more traffic
    if (work_done < budget) {
	napi_complete(napi);
        IFX_REG_W32_MASK(0, 1, MBOX_IGU1_IER);
        return work_done;
    }

    //  next round
    return work_done;
}