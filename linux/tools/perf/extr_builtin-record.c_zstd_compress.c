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
struct perf_session {size_t bytes_transferred; size_t bytes_compressed; int /*<<< orphan*/  zstd_data; } ;
struct perf_record_compressed {int dummy; } ;

/* Variables and functions */
 int PERF_SAMPLE_MAX_SIZE ; 
 int /*<<< orphan*/  process_comp_header ; 
 size_t zstd_compress_stream_to_records (int /*<<< orphan*/ *,void*,size_t,void*,size_t,size_t,int /*<<< orphan*/ ) ; 

__attribute__((used)) static size_t zstd_compress(struct perf_session *session, void *dst, size_t dst_size,
			    void *src, size_t src_size)
{
	size_t compressed;
	size_t max_record_size = PERF_SAMPLE_MAX_SIZE - sizeof(struct perf_record_compressed) - 1;

	compressed = zstd_compress_stream_to_records(&session->zstd_data, dst, dst_size, src, src_size,
						     max_record_size, process_comp_header);

	session->bytes_transferred += src_size;
	session->bytes_compressed  += compressed;

	return compressed;
}