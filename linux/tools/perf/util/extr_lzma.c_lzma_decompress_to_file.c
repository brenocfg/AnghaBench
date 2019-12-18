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
typedef  int /*<<< orphan*/  u8 ;
typedef  scalar_t__ ssize_t ;
struct TYPE_5__ {scalar_t__ avail_in; int avail_out; int /*<<< orphan*/ * next_out; int /*<<< orphan*/ * next_in; } ;
typedef  TYPE_1__ lzma_stream ;
typedef  scalar_t__ lzma_ret ;
typedef  int /*<<< orphan*/  lzma_action ;
typedef  int /*<<< orphan*/  buf_out ;
typedef  int /*<<< orphan*/  buf_in ;
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 int BUFSIZE ; 
 int /*<<< orphan*/  LZMA_CONCATENATED ; 
 int /*<<< orphan*/  LZMA_FINISH ; 
 scalar_t__ LZMA_OK ; 
 int /*<<< orphan*/  LZMA_RUN ; 
 scalar_t__ LZMA_STREAM_END ; 
 TYPE_1__ LZMA_STREAM_INIT ; 
 int /*<<< orphan*/  UINT64_MAX ; 
 int /*<<< orphan*/  errno ; 
 int /*<<< orphan*/  fclose (int /*<<< orphan*/ *) ; 
 scalar_t__ feof (int /*<<< orphan*/ *) ; 
 scalar_t__ ferror (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * fopen (char const*,char*) ; 
 scalar_t__ fread (int /*<<< orphan*/ *,int,int,int /*<<< orphan*/ *) ; 
 scalar_t__ lzma_code (TYPE_1__*,int /*<<< orphan*/ ) ; 
 scalar_t__ lzma_stream_decoder (TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lzma_strerror (scalar_t__) ; 
 int /*<<< orphan*/  pr_err (char*,char const*,...) ; 
 int /*<<< orphan*/  strerror (int /*<<< orphan*/ ) ; 
 scalar_t__ writen (int,int /*<<< orphan*/ *,scalar_t__) ; 

int lzma_decompress_to_file(const char *input, int output_fd)
{
	lzma_action action = LZMA_RUN;
	lzma_stream strm   = LZMA_STREAM_INIT;
	lzma_ret ret;
	int err = -1;

	u8 buf_in[BUFSIZE];
	u8 buf_out[BUFSIZE];
	FILE *infile;

	infile = fopen(input, "rb");
	if (!infile) {
		pr_err("lzma: fopen failed on %s: '%s'\n",
		       input, strerror(errno));
		return -1;
	}

	ret = lzma_stream_decoder(&strm, UINT64_MAX, LZMA_CONCATENATED);
	if (ret != LZMA_OK) {
		pr_err("lzma: lzma_stream_decoder failed %s (%d)\n",
			lzma_strerror(ret), ret);
		goto err_fclose;
	}

	strm.next_in   = NULL;
	strm.avail_in  = 0;
	strm.next_out  = buf_out;
	strm.avail_out = sizeof(buf_out);

	while (1) {
		if (strm.avail_in == 0 && !feof(infile)) {
			strm.next_in  = buf_in;
			strm.avail_in = fread(buf_in, 1, sizeof(buf_in), infile);

			if (ferror(infile)) {
				pr_err("lzma: read error: %s\n", strerror(errno));
				goto err_fclose;
			}

			if (feof(infile))
				action = LZMA_FINISH;
		}

		ret = lzma_code(&strm, action);

		if (strm.avail_out == 0 || ret == LZMA_STREAM_END) {
			ssize_t write_size = sizeof(buf_out) - strm.avail_out;

			if (writen(output_fd, buf_out, write_size) != write_size) {
				pr_err("lzma: write error: %s\n", strerror(errno));
				goto err_fclose;
			}

			strm.next_out  = buf_out;
			strm.avail_out = sizeof(buf_out);
		}

		if (ret != LZMA_OK) {
			if (ret == LZMA_STREAM_END)
				break;

			pr_err("lzma: failed %s\n", lzma_strerror(ret));
			goto err_fclose;
		}
	}

	err = 0;
err_fclose:
	fclose(infile);
	return err;
}