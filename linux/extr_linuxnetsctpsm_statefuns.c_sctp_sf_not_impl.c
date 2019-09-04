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
typedef  union sctp_subtype {int dummy; } sctp_subtype ;
struct sctp_endpoint {int dummy; } ;
struct sctp_cmd_seq {int dummy; } ;
struct sctp_association {int dummy; } ;
struct net {int dummy; } ;
typedef  enum sctp_disposition { ____Placeholder_sctp_disposition } sctp_disposition ;

/* Variables and functions */
 int SCTP_DISPOSITION_NOT_IMPL ; 

enum sctp_disposition sctp_sf_not_impl(struct net *net,
				       const struct sctp_endpoint *ep,
				       const struct sctp_association *asoc,
				       const union sctp_subtype type,
				       void *arg, struct sctp_cmd_seq *commands)
{
	return SCTP_DISPOSITION_NOT_IMPL;
}