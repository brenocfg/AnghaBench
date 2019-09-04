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
struct sctp_chunk {int dummy; } ;
struct sctp_association {int dummy; } ;
typedef  int /*<<< orphan*/  gfp_t ;
typedef  int /*<<< orphan*/  __u8 ;

/* Variables and functions */
 int /*<<< orphan*/  SCTP_CID_DATA ; 
 struct sctp_chunk* _sctp_make_chunk (struct sctp_association const*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static struct sctp_chunk *sctp_make_data(const struct sctp_association *asoc,
					 __u8 flags, int paylen, gfp_t gfp)
{
	return _sctp_make_chunk(asoc, SCTP_CID_DATA, flags, paylen, gfp);
}