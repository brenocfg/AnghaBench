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
struct gssx_cred {int /*<<< orphan*/  needs_release; int /*<<< orphan*/  cred_handle_reference; int /*<<< orphan*/  elements; int /*<<< orphan*/  desired_name; } ;

/* Variables and functions */
 int dummy_enc_credel_array (struct xdr_stream*,int /*<<< orphan*/ *) ; 
 int gssx_enc_bool (struct xdr_stream*,int /*<<< orphan*/ ) ; 
 int gssx_enc_buffer (struct xdr_stream*,int /*<<< orphan*/ *) ; 
 int gssx_enc_name (struct xdr_stream*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int gssx_enc_cred(struct xdr_stream *xdr,
			 struct gssx_cred *cred)
{
	int err;

	/* cred->desired_name */
	err = gssx_enc_name(xdr, &cred->desired_name);
	if (err)
		return err;

	/* cred->elements */
	err = dummy_enc_credel_array(xdr, &cred->elements);
	if (err)
		return err;

	/* cred->cred_handle_reference */
	err = gssx_enc_buffer(xdr, &cred->cred_handle_reference);
	if (err)
		return err;

	/* cred->needs_release */
	err = gssx_enc_bool(xdr, cred->needs_release);

	return err;
}