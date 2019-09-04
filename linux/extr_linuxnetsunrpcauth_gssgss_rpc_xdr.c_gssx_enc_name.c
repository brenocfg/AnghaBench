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
struct gssx_name {int /*<<< orphan*/  display_name; } ;

/* Variables and functions */
 int dummy_enc_nameattr_array (struct xdr_stream*,int /*<<< orphan*/ *) ; 
 int dummy_enc_opt_array (struct xdr_stream*,int /*<<< orphan*/ *) ; 
 int gssx_enc_buffer (struct xdr_stream*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  zero_name_attr_array ; 
 int /*<<< orphan*/  zero_netobj ; 
 int /*<<< orphan*/  zero_option_array ; 

__attribute__((used)) static int gssx_enc_name(struct xdr_stream *xdr,
			 struct gssx_name *name)
{
	int err;

	/* name->display_name */
	err = gssx_enc_buffer(xdr, &name->display_name);
	if (err)
		return err;

	/* name->name_type */
	err = gssx_enc_buffer(xdr, &zero_netobj);
	if (err)
		return err;

	/* name->exported_name */
	err = gssx_enc_buffer(xdr, &zero_netobj);
	if (err)
		return err;

	/* name->exported_composite_name */
	err = gssx_enc_buffer(xdr, &zero_netobj);
	if (err)
		return err;

	/* leave name_attributes empty for now, will add once we have any
	 * to pass up at all */
	/* name->name_attributes */
	err = dummy_enc_nameattr_array(xdr, &zero_name_attr_array);
	if (err)
		return err;

	/* leave options empty for now, will add once we have any options
	 * to pass up at all */
	/* name->extensions */
	err = dummy_enc_opt_array(xdr, &zero_option_array);

	return err;
}