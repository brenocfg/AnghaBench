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
struct gssx_option {int /*<<< orphan*/  value; int /*<<< orphan*/  option; } ;

/* Variables and functions */
 int gssx_enc_buffer (struct xdr_stream*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int gssx_enc_option(struct xdr_stream *xdr,
			   struct gssx_option *opt)
{
	int err;

	err = gssx_enc_buffer(xdr, &opt->option);
	if (err)
		return err;
	err = gssx_enc_buffer(xdr, &opt->value);
	return err;
}