#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct iw_request_info {int dummy; } ;
struct TYPE_3__ {int length; } ;
struct TYPE_4__ {TYPE_1__ data; } ;
struct iw_event {int len; TYPE_2__ u; } ;

/* Variables and functions */
 int IW_EV_LCP_PK_LEN ; 
 int IW_EV_POINT_OFF ; 
 int IW_EV_POINT_PK_LEN ; 
 int iwe_stream_lcp_len (struct iw_request_info*) ; 
 int iwe_stream_point_len (struct iw_request_info*) ; 
 scalar_t__ likely (int) ; 
 int /*<<< orphan*/  memcpy (char*,char*,int) ; 

char *iwe_stream_add_point(struct iw_request_info *info, char *stream,
			   char *ends, struct iw_event *iwe, char *extra)
{
	int event_len = iwe_stream_point_len(info) + iwe->u.data.length;
	int point_len = iwe_stream_point_len(info);
	int lcp_len   = iwe_stream_lcp_len(info);

	/* Check if it's possible */
	if (likely((stream + event_len) < ends)) {
		iwe->len = event_len;
		memcpy(stream, (char *) iwe, IW_EV_LCP_PK_LEN);
		memcpy(stream + lcp_len,
		       ((char *) &iwe->u) + IW_EV_POINT_OFF,
		       IW_EV_POINT_PK_LEN - IW_EV_LCP_PK_LEN);
		if (iwe->u.data.length && extra)
			memcpy(stream + point_len, extra, iwe->u.data.length);
		stream += event_len;
	}

	return stream;
}