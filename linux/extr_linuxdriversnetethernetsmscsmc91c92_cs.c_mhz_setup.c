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
typedef  char u8 ;
struct pcmcia_device {char** prod_id; struct net_device* priv; } ;
struct net_device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  CISTPL_VERS_1 ; 
 scalar_t__ cvt_ascii_address (struct net_device*,char*) ; 
 int /*<<< orphan*/  kfree (char*) ; 
 size_t pcmcia_get_tuple (struct pcmcia_device*,int,char**) ; 
 int /*<<< orphan*/  pcmcia_get_versmac ; 
 int /*<<< orphan*/  pcmcia_loop_tuple (struct pcmcia_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct net_device*) ; 

__attribute__((used)) static int mhz_setup(struct pcmcia_device *link)
{
    struct net_device *dev = link->priv;
    size_t len;
    u8 *buf;
    int rc;

    /* Read the station address from the CIS.  It is stored as the last
       (fourth) string in the Version 1 Version/ID tuple. */
    if ((link->prod_id[3]) &&
	(cvt_ascii_address(dev, link->prod_id[3]) == 0))
	    return 0;

    /* Workarounds for broken cards start here. */
    /* Ugh -- the EM1144 card has two VERS_1 tuples!?! */
    if (!pcmcia_loop_tuple(link, CISTPL_VERS_1, pcmcia_get_versmac, dev))
	    return 0;

    /* Another possibility: for the EM3288, in a special tuple */
    rc = -1;
    len = pcmcia_get_tuple(link, 0x81, &buf);
    if (buf && len >= 13) {
	    buf[12] = '\0';
	    if (cvt_ascii_address(dev, buf) == 0)
		    rc = 0;
    }
    kfree(buf);

    return rc;
}