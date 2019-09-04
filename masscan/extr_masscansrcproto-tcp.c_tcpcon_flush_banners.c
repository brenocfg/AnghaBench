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
struct BannerOutput {int protocol; scalar_t__ length; int /*<<< orphan*/  banner; struct BannerOutput* next; } ;
struct TCP_Control_Block {struct BannerOutput banout; int /*<<< orphan*/  ttl; int /*<<< orphan*/  port_them; int /*<<< orphan*/  ip_them; } ;
struct TCP_ConnectionTable {int /*<<< orphan*/  out; int /*<<< orphan*/  (* report_banner ) (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  banout_release (struct BannerOutput*) ; 
 int /*<<< orphan*/  global_now ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__) ; 

__attribute__((used)) static void
tcpcon_flush_banners(struct TCP_ConnectionTable *tcpcon, struct TCP_Control_Block *tcb)
{
    struct BannerOutput *banout;
    
    /* Go through and print all the banners. Some protocols have 
     * multiple banners. For example, web servers have both
     * HTTP and HTML banners, and SSL also has several 
     * X.509 certificate banners */
    for (banout = &tcb->banout; banout != NULL; banout = banout->next) {
        if (banout->length && banout->protocol) {
            tcpcon->report_banner(
                                  tcpcon->out,
                                  global_now,
                                  tcb->ip_them,
                                  6, /*TCP protocol*/
                                  tcb->port_them,
                                  banout->protocol & 0x0FFFFFFF,
                                  tcb->ttl,
                                  banout->banner,
                                  banout->length);
        }
    }
    
    /*
     * Free up all the banners.
     */
    banout_release(&tcb->banout);

}