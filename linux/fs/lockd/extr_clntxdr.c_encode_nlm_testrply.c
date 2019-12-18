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
struct xdr_stream {int dummy; } ;
struct nlm_res {scalar_t__ status; } ;

/* Variables and functions */
 int /*<<< orphan*/  encode_nlm_holder (struct xdr_stream*,struct nlm_res const*) ; 
 scalar_t__ nlm_lck_denied ; 

__attribute__((used)) static void encode_nlm_testrply(struct xdr_stream *xdr,
				const struct nlm_res *result)
{
	if (result->status == nlm_lck_denied)
		encode_nlm_holder(xdr, result);
}