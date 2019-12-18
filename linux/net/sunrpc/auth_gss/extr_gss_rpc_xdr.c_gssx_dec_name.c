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
struct xdr_netobj {int /*<<< orphan*/  len; } ;
struct gssx_option_array {int /*<<< orphan*/  count; } ;
struct gssx_name_attr_array {int /*<<< orphan*/  count; } ;
struct gssx_name {struct xdr_netobj display_name; } ;

/* Variables and functions */
 int dummy_dec_nameattr_array (struct xdr_stream*,struct gssx_name_attr_array*) ; 
 int dummy_dec_opt_array (struct xdr_stream*,struct gssx_option_array*) ; 
 int gssx_dec_buffer (struct xdr_stream*,struct xdr_netobj*) ; 

__attribute__((used)) static int gssx_dec_name(struct xdr_stream *xdr,
			 struct gssx_name *name)
{
	struct xdr_netobj dummy_netobj = { .len = 0 };
	struct gssx_name_attr_array dummy_name_attr_array = { .count = 0 };
	struct gssx_option_array dummy_option_array = { .count = 0 };
	int err;

	/* name->display_name */
	err = gssx_dec_buffer(xdr, &name->display_name);
	if (err)
		return err;

	/* name->name_type */
	err = gssx_dec_buffer(xdr, &dummy_netobj);
	if (err)
		return err;

	/* name->exported_name */
	err = gssx_dec_buffer(xdr, &dummy_netobj);
	if (err)
		return err;

	/* name->exported_composite_name */
	err = gssx_dec_buffer(xdr, &dummy_netobj);
	if (err)
		return err;

	/* we assume we have no attributes for now, so simply consume them */
	/* name->name_attributes */
	err = dummy_dec_nameattr_array(xdr, &dummy_name_attr_array);
	if (err)
		return err;

	/* we assume we have no options for now, so simply consume them */
	/* name->extensions */
	err = dummy_dec_opt_array(xdr, &dummy_option_array);

	return err;
}