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
struct TYPE_3__ {int options; int /*<<< orphan*/  mediaControlChannel; int /*<<< orphan*/  mediaChannel; } ;
typedef  TYPE_1__ H2250LogicalChannelParameters ;

/* Variables and functions */
 int eH2250LogicalChannelParameters_mediaChannel ; 
 int eH2250LogicalChannelParameters_mediaControlChannel ; 
 int expect_rtp_rtcp (struct sk_buff*,struct nf_conn*,int,unsigned int,unsigned char**,int,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int process_h245_channel(struct sk_buff *skb,
				struct nf_conn *ct,
				enum ip_conntrack_info ctinfo,
				unsigned int protoff,
				unsigned char **data, int dataoff,
				H2250LogicalChannelParameters *channel)
{
	int ret;

	if (channel->options & eH2250LogicalChannelParameters_mediaChannel) {
		/* RTP */
		ret = expect_rtp_rtcp(skb, ct, ctinfo, protoff, data, dataoff,
				      &channel->mediaChannel);
		if (ret < 0)
			return -1;
	}

	if (channel->
	    options & eH2250LogicalChannelParameters_mediaControlChannel) {
		/* RTCP */
		ret = expect_rtp_rtcp(skb, ct, ctinfo, protoff, data, dataoff,
				      &channel->mediaControlChannel);
		if (ret < 0)
			return -1;
	}

	return 0;
}