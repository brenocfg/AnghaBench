#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct sk_buff {int dummy; } ;
struct nf_conn {int dummy; } ;
typedef  enum ip_conntrack_info { ____Placeholder_ip_conntrack_info } ip_conntrack_info ;
struct TYPE_3__ {int choice; int /*<<< orphan*/  infoRequestResponse; int /*<<< orphan*/  locationConfirm; int /*<<< orphan*/  locationRequest; int /*<<< orphan*/  admissionConfirm; int /*<<< orphan*/  admissionRequest; int /*<<< orphan*/  unregistrationRequest; int /*<<< orphan*/  registrationConfirm; int /*<<< orphan*/  registrationRequest; int /*<<< orphan*/  gatekeeperConfirm; int /*<<< orphan*/  gatekeeperRequest; } ;
typedef  TYPE_1__ RasMessage ;

/* Variables and functions */
#define  eRasMessage_admissionConfirm 137 
#define  eRasMessage_admissionRequest 136 
#define  eRasMessage_gatekeeperConfirm 135 
#define  eRasMessage_gatekeeperRequest 134 
#define  eRasMessage_infoRequestResponse 133 
#define  eRasMessage_locationConfirm 132 
#define  eRasMessage_locationRequest 131 
#define  eRasMessage_registrationConfirm 130 
#define  eRasMessage_registrationRequest 129 
#define  eRasMessage_unregistrationRequest 128 
 int /*<<< orphan*/  pr_debug (char*,int) ; 
 int process_acf (struct sk_buff*,struct nf_conn*,int,unsigned int,unsigned char**,int /*<<< orphan*/ *) ; 
 int process_arq (struct sk_buff*,struct nf_conn*,int,unsigned int,unsigned char**,int /*<<< orphan*/ *) ; 
 int process_gcf (struct sk_buff*,struct nf_conn*,int,unsigned int,unsigned char**,int /*<<< orphan*/ *) ; 
 int process_grq (struct sk_buff*,struct nf_conn*,int,unsigned int,unsigned char**,int /*<<< orphan*/ *) ; 
 int process_irr (struct sk_buff*,struct nf_conn*,int,unsigned int,unsigned char**,int /*<<< orphan*/ *) ; 
 int process_lcf (struct sk_buff*,struct nf_conn*,int,unsigned int,unsigned char**,int /*<<< orphan*/ *) ; 
 int process_lrq (struct sk_buff*,struct nf_conn*,int,unsigned int,unsigned char**,int /*<<< orphan*/ *) ; 
 int process_rcf (struct sk_buff*,struct nf_conn*,int,unsigned int,unsigned char**,int /*<<< orphan*/ *) ; 
 int process_rrq (struct sk_buff*,struct nf_conn*,int,unsigned int,unsigned char**,int /*<<< orphan*/ *) ; 
 int process_urq (struct sk_buff*,struct nf_conn*,int,unsigned int,unsigned char**,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int process_ras(struct sk_buff *skb, struct nf_conn *ct,
		       enum ip_conntrack_info ctinfo,
		       unsigned int protoff,
		       unsigned char **data, RasMessage *ras)
{
	switch (ras->choice) {
	case eRasMessage_gatekeeperRequest:
		return process_grq(skb, ct, ctinfo, protoff, data,
				   &ras->gatekeeperRequest);
	case eRasMessage_gatekeeperConfirm:
		return process_gcf(skb, ct, ctinfo, protoff, data,
				   &ras->gatekeeperConfirm);
	case eRasMessage_registrationRequest:
		return process_rrq(skb, ct, ctinfo, protoff, data,
				   &ras->registrationRequest);
	case eRasMessage_registrationConfirm:
		return process_rcf(skb, ct, ctinfo, protoff, data,
				   &ras->registrationConfirm);
	case eRasMessage_unregistrationRequest:
		return process_urq(skb, ct, ctinfo, protoff, data,
				   &ras->unregistrationRequest);
	case eRasMessage_admissionRequest:
		return process_arq(skb, ct, ctinfo, protoff, data,
				   &ras->admissionRequest);
	case eRasMessage_admissionConfirm:
		return process_acf(skb, ct, ctinfo, protoff, data,
				   &ras->admissionConfirm);
	case eRasMessage_locationRequest:
		return process_lrq(skb, ct, ctinfo, protoff, data,
				   &ras->locationRequest);
	case eRasMessage_locationConfirm:
		return process_lcf(skb, ct, ctinfo, protoff, data,
				   &ras->locationConfirm);
	case eRasMessage_infoRequestResponse:
		return process_irr(skb, ct, ctinfo, protoff, data,
				   &ras->infoRequestResponse);
	default:
		pr_debug("nf_ct_ras: RAS message %d\n", ras->choice);
		break;
	}

	return 0;
}