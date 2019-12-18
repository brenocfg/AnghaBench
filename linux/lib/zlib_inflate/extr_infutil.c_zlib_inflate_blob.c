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
typedef  int /*<<< orphan*/  u8 ;
struct z_stream_s {unsigned int avail_in; unsigned int avail_out; struct z_stream_s* workspace; void* next_out; int /*<<< orphan*/  const* next_in; } ;

/* Variables and functions */
 int EINVAL ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  MAX_WBITS ; 
 int /*<<< orphan*/  Z_FINISH ; 
 int Z_OK ; 
 int Z_STREAM_END ; 
 int /*<<< orphan*/  kfree (struct z_stream_s*) ; 
 void* kmalloc (int,int /*<<< orphan*/ ) ; 
 int zlib_inflate (struct z_stream_s*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  zlib_inflateEnd (struct z_stream_s*) ; 
 int zlib_inflateInit2 (struct z_stream_s*,int /*<<< orphan*/ ) ; 
 int zlib_inflate_workspacesize () ; 

int zlib_inflate_blob(void *gunzip_buf, unsigned int sz,
		      const void *buf, unsigned int len)
{
	const u8 *zbuf = buf;
	struct z_stream_s *strm;
	int rc;

	rc = -ENOMEM;
	strm = kmalloc(sizeof(*strm), GFP_KERNEL);
	if (strm == NULL)
		goto gunzip_nomem1;
	strm->workspace = kmalloc(zlib_inflate_workspacesize(), GFP_KERNEL);
	if (strm->workspace == NULL)
		goto gunzip_nomem2;

	/* gzip header (1f,8b,08... 10 bytes total + possible asciz filename)
	 * expected to be stripped from input
	 */
	strm->next_in = zbuf;
	strm->avail_in = len;
	strm->next_out = gunzip_buf;
	strm->avail_out = sz;

	rc = zlib_inflateInit2(strm, -MAX_WBITS);
	if (rc == Z_OK) {
		rc = zlib_inflate(strm, Z_FINISH);
		/* after Z_FINISH, only Z_STREAM_END is "we unpacked it all" */
		if (rc == Z_STREAM_END)
			rc = sz - strm->avail_out;
		else
			rc = -EINVAL;
		zlib_inflateEnd(strm);
	} else
		rc = -EINVAL;

	kfree(strm->workspace);
gunzip_nomem2:
	kfree(strm);
gunzip_nomem1:
	return rc; /* returns Z_OK (0) if successful */
}