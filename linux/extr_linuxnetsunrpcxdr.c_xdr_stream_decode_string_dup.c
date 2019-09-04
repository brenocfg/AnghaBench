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
typedef  int ssize_t ;
typedef  int /*<<< orphan*/  gfp_t ;

/* Variables and functions */
 int ENOMEM ; 
 char* kmalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (char*,void*,int) ; 
 int strlen (char*) ; 
 int xdr_stream_decode_opaque_inline (struct xdr_stream*,void**,size_t) ; 

ssize_t xdr_stream_decode_string_dup(struct xdr_stream *xdr, char **str,
		size_t maxlen, gfp_t gfp_flags)
{
	void *p;
	ssize_t ret;

	ret = xdr_stream_decode_opaque_inline(xdr, &p, maxlen);
	if (ret > 0) {
		char *s = kmalloc(ret + 1, gfp_flags);
		if (s != NULL) {
			memcpy(s, p, ret);
			s[ret] = '\0';
			*str = s;
			return strlen(s);
		}
		ret = -ENOMEM;
	}
	*str = NULL;
	return ret;
}