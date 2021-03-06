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
struct nsm_args {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  encode_mon_name (struct xdr_stream*,struct nsm_args const*) ; 
 int /*<<< orphan*/  encode_my_id (struct xdr_stream*,struct nsm_args const*) ; 

__attribute__((used)) static void encode_mon_id(struct xdr_stream *xdr, const struct nsm_args *argp)
{
	encode_mon_name(xdr, argp);
	encode_my_id(xdr, argp);
}