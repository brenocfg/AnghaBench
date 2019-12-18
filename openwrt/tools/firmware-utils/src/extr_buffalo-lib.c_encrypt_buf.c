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
typedef  size_t uint32_t ;
struct enc_param {unsigned char seed; size_t datalen; size_t csum; int /*<<< orphan*/  longstate; int /*<<< orphan*/  key; scalar_t__ version; scalar_t__ product; scalar_t__ magic; } ;

/* Variables and functions */
 int bcrypt_buf (unsigned char,int /*<<< orphan*/ ,unsigned char*,unsigned char*,size_t,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (unsigned char*,scalar_t__,size_t) ; 
 int /*<<< orphan*/  put_be32 (unsigned char*,size_t) ; 
 size_t strlen (char*) ; 

int encrypt_buf(struct enc_param *ep, unsigned char *hdr,
		unsigned char *data)
{
	unsigned char *p;
	uint32_t len;
	int err;
	int ret = -1;
	unsigned char s;

	p = (unsigned char *) hdr;

	/* setup magic */
	len = strlen((char *) ep->magic) + 1;
	memcpy(p, ep->magic, len);
	p += len;

	/* setup seed */
	*p++ = ep->seed;

	/* put product len */
	len = strlen((char *) ep->product) + 1;
	put_be32(p, len);
	p += sizeof(uint32_t);

	/* copy and crypt product name */
	memcpy(p, ep->product, len);
	err = bcrypt_buf(ep->seed, ep->key, p, p, len, ep->longstate);
	if (err)
		goto out;
	s = *p;
	p += len;

	/* put version length */
	len = strlen((char *) ep->version) + 1;
	put_be32(p, len);
	p += sizeof(uint32_t);

	/* copy and crypt version */
	memcpy(p, ep->version, len);
	err = bcrypt_buf(s, ep->key, p, p, len, ep->longstate);
	if (err)
		goto out;
	s = *p;
	p += len;

	/* put data length */
	put_be32(p, ep->datalen);

	/* encrypt data */
	err = bcrypt_buf(s, ep->key, data, data, ep->datalen, ep->longstate);
	if (err)
		goto out;

	/* put checksum */
	put_be32(&data[ep->datalen], ep->csum);

	ret = 0;

out:
	return ret;
}