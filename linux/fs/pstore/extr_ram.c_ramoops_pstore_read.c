#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct ramoops_context {scalar_t__ dump_read_cnt; scalar_t__ max_dump_cnt; int flags; scalar_t__ ftrace_read_cnt; scalar_t__ max_ftrace_cnt; int /*<<< orphan*/ * fprzs; int /*<<< orphan*/  mprz; int /*<<< orphan*/  pmsg_read_cnt; int /*<<< orphan*/  cprz; int /*<<< orphan*/  console_read_cnt; int /*<<< orphan*/ * dprzs; } ;
struct TYPE_4__ {scalar_t__ tv_nsec; scalar_t__ tv_sec; } ;
struct pstore_record {int compressed; scalar_t__ ecc_notice_size; int /*<<< orphan*/ * buf; scalar_t__ id; TYPE_2__ time; TYPE_1__* psi; } ;
struct persistent_ram_zone {struct persistent_ram_zone* old_log; scalar_t__ bad_blocks; scalar_t__ corrected_bytes; int /*<<< orphan*/  ecc_info; } ;
typedef  int ssize_t ;
struct TYPE_3__ {struct ramoops_context* data; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int RAMOOPS_FLAG_FTRACE_PER_CPU ; 
 int ftrace_log_combine (struct persistent_ram_zone*,struct persistent_ram_zone*) ; 
 int /*<<< orphan*/  kfree (struct persistent_ram_zone*) ; 
 int /*<<< orphan*/ * kmalloc (scalar_t__,int /*<<< orphan*/ ) ; 
 struct persistent_ram_zone* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,char*,int) ; 
 scalar_t__ persistent_ram_ecc_string (struct persistent_ram_zone*,int /*<<< orphan*/ *,scalar_t__) ; 
 int /*<<< orphan*/  persistent_ram_free_old (struct persistent_ram_zone*) ; 
 scalar_t__ persistent_ram_old (struct persistent_ram_zone*) ; 
 int persistent_ram_old_size (struct persistent_ram_zone*) ; 
 int /*<<< orphan*/  persistent_ram_zap (struct persistent_ram_zone*) ; 
 int /*<<< orphan*/  prz_ok (struct persistent_ram_zone*) ; 
 struct persistent_ram_zone* ramoops_get_next_prz (int /*<<< orphan*/ *,int /*<<< orphan*/ ,struct pstore_record*) ; 
 int ramoops_read_kmsg_hdr (scalar_t__,TYPE_2__*,int*) ; 

__attribute__((used)) static ssize_t ramoops_pstore_read(struct pstore_record *record)
{
	ssize_t size = 0;
	struct ramoops_context *cxt = record->psi->data;
	struct persistent_ram_zone *prz = NULL;
	int header_length = 0;
	bool free_prz = false;

	/*
	 * Ramoops headers provide time stamps for PSTORE_TYPE_DMESG, but
	 * PSTORE_TYPE_CONSOLE and PSTORE_TYPE_FTRACE don't currently have
	 * valid time stamps, so it is initialized to zero.
	 */
	record->time.tv_sec = 0;
	record->time.tv_nsec = 0;
	record->compressed = false;

	/* Find the next valid persistent_ram_zone for DMESG */
	while (cxt->dump_read_cnt < cxt->max_dump_cnt && !prz) {
		prz = ramoops_get_next_prz(cxt->dprzs, cxt->dump_read_cnt++,
					   record);
		if (!prz_ok(prz))
			continue;
		header_length = ramoops_read_kmsg_hdr(persistent_ram_old(prz),
						      &record->time,
						      &record->compressed);
		/* Clear and skip this DMESG record if it has no valid header */
		if (!header_length) {
			persistent_ram_free_old(prz);
			persistent_ram_zap(prz);
			prz = NULL;
		}
	}

	if (!prz_ok(prz) && !cxt->console_read_cnt++)
		prz = ramoops_get_next_prz(&cxt->cprz, 0 /* single */, record);

	if (!prz_ok(prz) && !cxt->pmsg_read_cnt++)
		prz = ramoops_get_next_prz(&cxt->mprz, 0 /* single */, record);

	/* ftrace is last since it may want to dynamically allocate memory. */
	if (!prz_ok(prz)) {
		if (!(cxt->flags & RAMOOPS_FLAG_FTRACE_PER_CPU) &&
		    !cxt->ftrace_read_cnt++) {
			prz = ramoops_get_next_prz(cxt->fprzs, 0 /* single */,
						   record);
		} else {
			/*
			 * Build a new dummy record which combines all the
			 * per-cpu records including metadata and ecc info.
			 */
			struct persistent_ram_zone *tmp_prz, *prz_next;

			tmp_prz = kzalloc(sizeof(struct persistent_ram_zone),
					  GFP_KERNEL);
			if (!tmp_prz)
				return -ENOMEM;
			prz = tmp_prz;
			free_prz = true;

			while (cxt->ftrace_read_cnt < cxt->max_ftrace_cnt) {
				prz_next = ramoops_get_next_prz(cxt->fprzs,
						cxt->ftrace_read_cnt++, record);

				if (!prz_ok(prz_next))
					continue;

				tmp_prz->ecc_info = prz_next->ecc_info;
				tmp_prz->corrected_bytes +=
						prz_next->corrected_bytes;
				tmp_prz->bad_blocks += prz_next->bad_blocks;
				size = ftrace_log_combine(tmp_prz, prz_next);
				if (size)
					goto out;
			}
			record->id = 0;
		}
	}

	if (!prz_ok(prz)) {
		size = 0;
		goto out;
	}

	size = persistent_ram_old_size(prz) - header_length;

	/* ECC correction notice */
	record->ecc_notice_size = persistent_ram_ecc_string(prz, NULL, 0);

	record->buf = kmalloc(size + record->ecc_notice_size + 1, GFP_KERNEL);
	if (record->buf == NULL) {
		size = -ENOMEM;
		goto out;
	}

	memcpy(record->buf, (char *)persistent_ram_old(prz) + header_length,
	       size);

	persistent_ram_ecc_string(prz, record->buf + size,
				  record->ecc_notice_size + 1);

out:
	if (free_prz) {
		kfree(prz->old_log);
		kfree(prz);
	}

	return size;
}