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
struct gssx_name_attr {int /*<<< orphan*/  extensions; int /*<<< orphan*/  value; int /*<<< orphan*/  attr; } ;

/* Variables and functions */
 int dummy_dec_opt_array (struct xdr_stream*,int /*<<< orphan*/ *) ; 
 int gssx_dec_buffer (struct xdr_stream*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int gssx_dec_name_attr(struct xdr_stream *xdr,
			     struct gssx_name_attr *attr)
{
	int err;

	/* attr->attr */
	err = gssx_dec_buffer(xdr, &attr->attr);
	if (err)
		return err;

	/* attr->value */
	err = gssx_dec_buffer(xdr, &attr->value);
	if (err)
		return err;

	/* attr->extensions */
	err = dummy_dec_opt_array(xdr, &attr->extensions);

	return err;
}