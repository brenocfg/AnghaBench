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
struct cfrfml {scalar_t__ pdu_size; int /*<<< orphan*/  incomplete_frm; int /*<<< orphan*/  seghead; } ;
struct cfpkt {int dummy; } ;

/* Variables and functions */
 int ENOMEM ; 
 int EPROTO ; 
 scalar_t__ RFM_HEAD_SIZE ; 
 struct cfpkt* cfpkt_append (int /*<<< orphan*/ ,struct cfpkt*,scalar_t__) ; 
 scalar_t__ cfpkt_extr_head (struct cfpkt*,char*,int) ; 
 scalar_t__ memcmp (char*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static struct cfpkt *rfm_append(struct cfrfml *rfml, char *seghead,
				struct cfpkt *pkt, int *err)
{
	struct cfpkt *tmppkt;
	*err = -EPROTO;
	/* n-th but not last segment */

	if (cfpkt_extr_head(pkt, seghead, 6) < 0)
		return NULL;

	/* Verify correct header */
	if (memcmp(seghead, rfml->seghead, 6) != 0)
		return NULL;

	tmppkt = cfpkt_append(rfml->incomplete_frm, pkt,
			rfml->pdu_size + RFM_HEAD_SIZE);

	/* If cfpkt_append failes input pkts are not freed */
	*err = -ENOMEM;
	if (tmppkt == NULL)
		return NULL;

	*err = 0;
	return tmppkt;
}