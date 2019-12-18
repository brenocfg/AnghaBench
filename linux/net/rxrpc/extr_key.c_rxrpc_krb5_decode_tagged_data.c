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
struct krb5_tagged_data {unsigned int data_len; void* tag; int /*<<< orphan*/  data; } ;
typedef  int /*<<< orphan*/  __be32 ;

/* Variables and functions */
 int EINVAL ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  _debug (char*,void*,unsigned int) ; 
 int /*<<< orphan*/  _enter (char*,size_t,void*,void*,unsigned int) ; 
 int /*<<< orphan*/  _leave (char*,unsigned int) ; 
 int /*<<< orphan*/  kmemdup (int /*<<< orphan*/  const*,unsigned int,int /*<<< orphan*/ ) ; 
 void* ntohl (int /*<<< orphan*/  const) ; 

__attribute__((used)) static int rxrpc_krb5_decode_tagged_data(struct krb5_tagged_data *td,
					 size_t max_data_size,
					 const __be32 **_xdr,
					 unsigned int *_toklen)
{
	const __be32 *xdr = *_xdr;
	unsigned int toklen = *_toklen, len, paddedlen;

	/* there must be at least one tag and one length word */
	if (toklen <= 8)
		return -EINVAL;

	_enter(",%zu,{%x,%x},%u",
	       max_data_size, ntohl(xdr[0]), ntohl(xdr[1]), toklen);

	td->tag = ntohl(*xdr++);
	len = ntohl(*xdr++);
	toklen -= 8;
	if (len > max_data_size)
		return -EINVAL;
	paddedlen = (len + 3) & ~3;
	if (paddedlen > toklen)
		return -EINVAL;
	td->data_len = len;

	if (len > 0) {
		td->data = kmemdup(xdr, len, GFP_KERNEL);
		if (!td->data)
			return -ENOMEM;
		toklen -= paddedlen;
		xdr += paddedlen >> 2;
	}

	_debug("tag %x len %x", td->tag, td->data_len);

	*_xdr = xdr;
	*_toklen = toklen;
	_leave(" = 0 [toklen=%u]", toklen);
	return 0;
}