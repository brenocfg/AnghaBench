#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int uint32_t ;
struct TYPE_5__ {unsigned char* next_in; int avail_in; unsigned char* next_out; int avail_out; scalar_t__ total_out; scalar_t__ total_in; } ;

/* Variables and functions */
 int MAX_WBITS ; 
 unsigned char PRESET_DICT ; 
 unsigned char Z_DEFLATED ; 
 int /*<<< orphan*/  Z_FINISH ; 
 int Z_OK ; 
 int Z_STREAM_END ; 
 TYPE_1__ inf_strm ; 
 int /*<<< orphan*/  inflate_mutex ; 
 int /*<<< orphan*/  jffs2_dbg (int,char*) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pr_notice (char*,int) ; 
 int /*<<< orphan*/  pr_warn (char*) ; 
 int zlib_inflate (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  zlib_inflateEnd (TYPE_1__*) ; 
 int zlib_inflateInit2 (TYPE_1__*,int) ; 

__attribute__((used)) static int jffs2_zlib_decompress(unsigned char *data_in,
				 unsigned char *cpage_out,
				 uint32_t srclen, uint32_t destlen)
{
	int ret;
	int wbits = MAX_WBITS;

	mutex_lock(&inflate_mutex);

	inf_strm.next_in = data_in;
	inf_strm.avail_in = srclen;
	inf_strm.total_in = 0;

	inf_strm.next_out = cpage_out;
	inf_strm.avail_out = destlen;
	inf_strm.total_out = 0;

	/* If it's deflate, and it's got no preset dictionary, then
	   we can tell zlib to skip the adler32 check. */
	if (srclen > 2 && !(data_in[1] & PRESET_DICT) &&
	    ((data_in[0] & 0x0f) == Z_DEFLATED) &&
	    !(((data_in[0]<<8) + data_in[1]) % 31)) {

		jffs2_dbg(2, "inflate skipping adler32\n");
		wbits = -((data_in[0] >> 4) + 8);
		inf_strm.next_in += 2;
		inf_strm.avail_in -= 2;
	} else {
		/* Let this remain D1 for now -- it should never happen */
		jffs2_dbg(1, "inflate not skipping adler32\n");
	}


	if (Z_OK != zlib_inflateInit2(&inf_strm, wbits)) {
		pr_warn("inflateInit failed\n");
		mutex_unlock(&inflate_mutex);
		return 1;
	}

	while((ret = zlib_inflate(&inf_strm, Z_FINISH)) == Z_OK)
		;
	if (ret != Z_STREAM_END) {
		pr_notice("inflate returned %d\n", ret);
	}
	zlib_inflateEnd(&inf_strm);
	mutex_unlock(&inflate_mutex);
	return 0;
}