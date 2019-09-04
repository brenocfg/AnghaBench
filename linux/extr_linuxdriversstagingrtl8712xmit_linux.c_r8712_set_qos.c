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
typedef  unsigned char u8 ;
typedef  int u16 ;
struct pkt_file {int /*<<< orphan*/  pkt; } ;
struct pkt_attrib {int ether_type; int priority; int /*<<< orphan*/  subtype; int /*<<< orphan*/  hdrlen; } ;
struct iphdr {int tos; } ;
struct ethhdr {int dummy; } ;
typedef  int /*<<< orphan*/  ip_hdr ;

/* Variables and functions */
 int ETH_HLEN ; 
 int /*<<< orphan*/  WIFI_QOS_DATA_TYPE ; 
 int /*<<< orphan*/  WLAN_HDR_A3_QOS_LEN ; 
 int /*<<< orphan*/  _r8712_open_pktfile (int /*<<< orphan*/ ,struct pkt_file*) ; 
 int /*<<< orphan*/  _r8712_pktfile_read (struct pkt_file*,unsigned char*,int) ; 

void r8712_set_qos(struct pkt_file *ppktfile, struct pkt_attrib *pattrib)
{
	struct ethhdr etherhdr;
	struct iphdr ip_hdr;
	u16 UserPriority = 0;

	_r8712_open_pktfile(ppktfile->pkt, ppktfile);
	_r8712_pktfile_read(ppktfile, (unsigned char *)&etherhdr, ETH_HLEN);

	/* get UserPriority from IP hdr*/
	if (pattrib->ether_type == 0x0800) {
		_r8712_pktfile_read(ppktfile, (u8 *)&ip_hdr, sizeof(ip_hdr));
		/*UserPriority = (ntohs(ip_hdr.tos) >> 5) & 0x3 ;*/
		UserPriority = ip_hdr.tos >> 5;
	} else {
		/* "When priority processing of data frames is supported,
		 * a STA's SME should send EAPOL-Key frames at the highest
		 * priority."
		 */

		if (pattrib->ether_type == 0x888e)
			UserPriority = 7;
	}
	pattrib->priority = UserPriority;
	pattrib->hdrlen = WLAN_HDR_A3_QOS_LEN;
	pattrib->subtype = WIFI_QOS_DATA_TYPE;
}