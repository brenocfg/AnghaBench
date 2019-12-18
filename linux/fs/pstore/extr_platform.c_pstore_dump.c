#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct pstore_record {int count; int reason; unsigned int part; char* buf; int compressed; int size; int /*<<< orphan*/  type; } ;
struct kmsg_dumper {int dummy; } ;
typedef  enum kmsg_dump_reason { ____Placeholder_kmsg_dump_reason } kmsg_dump_reason ;
struct TYPE_3__ {char* buf; size_t bufsize; int (* write ) (struct pstore_record*) ;int /*<<< orphan*/  buf_lock; } ;

/* Variables and functions */
 int KMSG_DUMP_OOPS ; 
 int /*<<< orphan*/  PSTORE_TYPE_DMESG ; 
 char* big_oops_buf ; 
 size_t big_oops_buf_sz ; 
 int copy_kmsg_to_buffer (int,size_t) ; 
 scalar_t__ down_interruptible (int /*<<< orphan*/ *) ; 
 scalar_t__ down_trylock (int /*<<< orphan*/ *) ; 
 char* get_reason_str (int) ; 
 scalar_t__ in_nmi () ; 
 unsigned long kmsg_bytes ; 
 int /*<<< orphan*/  kmsg_dump_get_buffer (struct kmsg_dumper*,int,char*,size_t,size_t*) ; 
 int oopscount ; 
 int /*<<< orphan*/  pr_err (char*,...) ; 
 TYPE_1__* psinfo ; 
 scalar_t__ pstore_cannot_wait (int) ; 
 int pstore_compress (char*,char*,int,size_t) ; 
 scalar_t__ pstore_is_mounted () ; 
 int pstore_new_entry ; 
 int /*<<< orphan*/  pstore_record_init (struct pstore_record*,TYPE_1__*) ; 
 int snprintf (char*,size_t,char*,char const*,int,unsigned int) ; 
 int stub1 (struct pstore_record*) ; 
 int /*<<< orphan*/  up (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void pstore_dump(struct kmsg_dumper *dumper,
			enum kmsg_dump_reason reason)
{
	unsigned long	total = 0;
	const char	*why;
	unsigned int	part = 1;
	int		ret;

	why = get_reason_str(reason);

	if (down_trylock(&psinfo->buf_lock)) {
		/* Failed to acquire lock: give up if we cannot wait. */
		if (pstore_cannot_wait(reason)) {
			pr_err("dump skipped in %s path: may corrupt error record\n",
				in_nmi() ? "NMI" : why);
			return;
		}
		if (down_interruptible(&psinfo->buf_lock)) {
			pr_err("could not grab semaphore?!\n");
			return;
		}
	}

	oopscount++;
	while (total < kmsg_bytes) {
		char *dst;
		size_t dst_size;
		int header_size;
		int zipped_len = -1;
		size_t dump_size;
		struct pstore_record record;

		pstore_record_init(&record, psinfo);
		record.type = PSTORE_TYPE_DMESG;
		record.count = oopscount;
		record.reason = reason;
		record.part = part;
		record.buf = psinfo->buf;

		if (big_oops_buf) {
			dst = big_oops_buf;
			dst_size = big_oops_buf_sz;
		} else {
			dst = psinfo->buf;
			dst_size = psinfo->bufsize;
		}

		/* Write dump header. */
		header_size = snprintf(dst, dst_size, "%s#%d Part%u\n", why,
				 oopscount, part);
		dst_size -= header_size;

		/* Write dump contents. */
		if (!kmsg_dump_get_buffer(dumper, true, dst + header_size,
					  dst_size, &dump_size))
			break;

		if (big_oops_buf) {
			zipped_len = pstore_compress(dst, psinfo->buf,
						header_size + dump_size,
						psinfo->bufsize);

			if (zipped_len > 0) {
				record.compressed = true;
				record.size = zipped_len;
			} else {
				record.size = copy_kmsg_to_buffer(header_size,
								  dump_size);
			}
		} else {
			record.size = header_size + dump_size;
		}

		ret = psinfo->write(&record);
		if (ret == 0 && reason == KMSG_DUMP_OOPS && pstore_is_mounted())
			pstore_new_entry = 1;

		total += record.size;
		part++;
	}

	up(&psinfo->buf_lock);
}