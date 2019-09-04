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
struct iw_request_info {int dummy; } ;
struct iw_event {int len; char u; } ;

/* Variables and functions */
 int IW_EV_LCP_PK_LEN ; 
 int iwe_stream_event_len_adjust (struct iw_request_info*,int) ; 
 int iwe_stream_lcp_len (struct iw_request_info*) ; 
 scalar_t__ likely (int) ; 
 int /*<<< orphan*/  memcpy (char*,char*,int) ; 

char *iwe_stream_add_event(struct iw_request_info *info, char *stream,
			   char *ends, struct iw_event *iwe, int event_len)
{
	int lcp_len = iwe_stream_lcp_len(info);

	event_len = iwe_stream_event_len_adjust(info, event_len);

	/* Check if it's possible */
	if (likely((stream + event_len) < ends)) {
		iwe->len = event_len;
		/* Beware of alignement issues on 64 bits */
		memcpy(stream, (char *) iwe, IW_EV_LCP_PK_LEN);
		memcpy(stream + lcp_len, &iwe->u,
		       event_len - lcp_len);
		stream += event_len;
	}

	return stream;
}