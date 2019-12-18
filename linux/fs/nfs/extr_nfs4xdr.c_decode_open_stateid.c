#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct xdr_stream {int dummy; } ;
struct TYPE_4__ {int /*<<< orphan*/  type; } ;
typedef  TYPE_1__ nfs4_stateid ;

/* Variables and functions */
 int /*<<< orphan*/  NFS4_OPEN_STATEID_TYPE ; 
 int decode_stateid (struct xdr_stream*,TYPE_1__*) ; 

__attribute__((used)) static int decode_open_stateid(struct xdr_stream *xdr, nfs4_stateid *stateid)
{
	stateid->type = NFS4_OPEN_STATEID_TYPE;
	return decode_stateid(xdr, stateid);
}