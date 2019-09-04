#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_19__   TYPE_4__ ;
typedef  struct TYPE_18__   TYPE_3__ ;
typedef  struct TYPE_17__   TYPE_2__ ;
typedef  struct TYPE_16__   TYPE_1__ ;
typedef  struct TYPE_15__   TYPE_13__ ;

/* Type definitions */
struct TYPE_15__ {size_t avail_in; scalar_t__ avail_out; scalar_t__ next_out; int /*<<< orphan*/  next_in; } ;
struct TYPE_16__ {char finished; size_t inbuf_len; scalar_t__ outbuf_len; scalar_t__ outbuf; TYPE_13__ strm; int /*<<< orphan*/  inbuf; } ;
typedef  TYPE_1__ php_zlib_filter_data ;
typedef  int /*<<< orphan*/  php_stream_filter_status_t ;
struct TYPE_17__ {int /*<<< orphan*/  abstract; } ;
typedef  TYPE_2__ php_stream_filter ;
struct TYPE_18__ {scalar_t__ head; } ;
typedef  TYPE_3__ php_stream_bucket_brigade ;
struct TYPE_19__ {size_t buflen; scalar_t__ buf; } ;
typedef  TYPE_4__ php_stream_bucket ;
typedef  int /*<<< orphan*/  php_stream ;

/* Variables and functions */
 int /*<<< orphan*/  PSFS_ERR_FATAL ; 
 int /*<<< orphan*/  PSFS_FEED_ME ; 
 int PSFS_FLAG_FLUSH_CLOSE ; 
 int /*<<< orphan*/  PSFS_PASS_ON ; 
 int /*<<< orphan*/  Z_FINISH ; 
 int Z_OK ; 
 scalar_t__ Z_PTR (int /*<<< orphan*/ ) ; 
 int Z_STREAM_END ; 
 int /*<<< orphan*/  Z_SYNC_FLUSH ; 
 int /*<<< orphan*/  estrndup (char*,size_t) ; 
 int inflate (TYPE_13__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  inflateEnd (TYPE_13__*) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,scalar_t__,size_t) ; 
 int /*<<< orphan*/  php_stream_bucket_append (TYPE_3__*,TYPE_4__*) ; 
 int /*<<< orphan*/  php_stream_bucket_delref (TYPE_4__*) ; 
 TYPE_4__* php_stream_bucket_make_writeable (scalar_t__) ; 
 TYPE_4__* php_stream_bucket_new (int /*<<< orphan*/ *,int /*<<< orphan*/ ,size_t,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static php_stream_filter_status_t php_zlib_inflate_filter(
	php_stream *stream,
	php_stream_filter *thisfilter,
	php_stream_bucket_brigade *buckets_in,
	php_stream_bucket_brigade *buckets_out,
	size_t *bytes_consumed,
	int flags
	)
{
	php_zlib_filter_data *data;
	php_stream_bucket *bucket;
	size_t consumed = 0;
	int status;
	php_stream_filter_status_t exit_status = PSFS_FEED_ME;

	if (!thisfilter || !Z_PTR(thisfilter->abstract)) {
		/* Should never happen */
		return PSFS_ERR_FATAL;
	}

	data = (php_zlib_filter_data *)(Z_PTR(thisfilter->abstract));

	while (buckets_in->head) {
		size_t bin = 0, desired;

		bucket = php_stream_bucket_make_writeable(buckets_in->head);

		while (bin < (unsigned int) bucket->buflen && !data->finished) {

			desired = bucket->buflen - bin;
			if (desired > data->inbuf_len) {
				desired = data->inbuf_len;
			}
			memcpy(data->strm.next_in, bucket->buf + bin, desired);
			data->strm.avail_in = desired;

			status = inflate(&(data->strm), flags & PSFS_FLAG_FLUSH_CLOSE ? Z_FINISH : Z_SYNC_FLUSH);
			if (status == Z_STREAM_END) {
				inflateEnd(&(data->strm));
				data->finished = '\1';
				exit_status = PSFS_PASS_ON;
			} else if (status != Z_OK) {
				/* Something bad happened */
				php_stream_bucket_delref(bucket);
				/* reset these because despite the error the filter may be used again */
				data->strm.next_in = data->inbuf;
				data->strm.avail_in = 0;
				return PSFS_ERR_FATAL;
			}
			desired -= data->strm.avail_in; /* desired becomes what we consumed this round through */
			data->strm.next_in = data->inbuf;
			data->strm.avail_in = 0;
			bin += desired;

			if (data->strm.avail_out < data->outbuf_len) {
				php_stream_bucket *out_bucket;
				size_t bucketlen = data->outbuf_len - data->strm.avail_out;
				out_bucket = php_stream_bucket_new(
					stream, estrndup((char *) data->outbuf, bucketlen), bucketlen, 1, 0);
				php_stream_bucket_append(buckets_out, out_bucket);
				data->strm.avail_out = data->outbuf_len;
				data->strm.next_out = data->outbuf;
				exit_status = PSFS_PASS_ON;
			}

		}
		consumed += bucket->buflen;
		php_stream_bucket_delref(bucket);
	}

	if (!data->finished && flags & PSFS_FLAG_FLUSH_CLOSE) {
		/* Spit it out! */
		status = Z_OK;
		while (status == Z_OK) {
			status = inflate(&(data->strm), Z_FINISH);
			if (data->strm.avail_out < data->outbuf_len) {
				size_t bucketlen = data->outbuf_len - data->strm.avail_out;

				bucket = php_stream_bucket_new(
					stream, estrndup((char *) data->outbuf, bucketlen), bucketlen, 1, 0);
				php_stream_bucket_append(buckets_out, bucket);
				data->strm.avail_out = data->outbuf_len;
				data->strm.next_out = data->outbuf;
				exit_status = PSFS_PASS_ON;
			}
		}
	}

	if (bytes_consumed) {
		*bytes_consumed = consumed;
	}

	return exit_status;
}