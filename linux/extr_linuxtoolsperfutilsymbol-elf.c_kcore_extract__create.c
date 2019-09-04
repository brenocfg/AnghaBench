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
struct kcore_extract {int /*<<< orphan*/  extract_filename; int /*<<< orphan*/  len; int /*<<< orphan*/  offs; int /*<<< orphan*/  addr; int /*<<< orphan*/  kcore_filename; } ;
struct kcore {int /*<<< orphan*/  fd; int /*<<< orphan*/  elfclass; } ;
typedef  scalar_t__ off_t ;

/* Variables and functions */
 int /*<<< orphan*/  PERF_KCORE_EXTRACT ; 
 scalar_t__ copy_bytes (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ) ; 
 scalar_t__ kcore__add_phdr (struct kcore*,int,scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kcore__close (struct kcore*) ; 
 scalar_t__ kcore__copy_hdr (struct kcore*,struct kcore*,size_t) ; 
 scalar_t__ kcore__init (struct kcore*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 scalar_t__ kcore__open (struct kcore*,int /*<<< orphan*/ ) ; 
 scalar_t__ kcore__write (struct kcore*) ; 
 scalar_t__ page_size ; 
 int /*<<< orphan*/  strcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  unlink (int /*<<< orphan*/ ) ; 

int kcore_extract__create(struct kcore_extract *kce)
{
	struct kcore kcore;
	struct kcore extract;
	size_t count = 1;
	int idx = 0, err = -1;
	off_t offset = page_size, sz;

	if (kcore__open(&kcore, kce->kcore_filename))
		return -1;

	strcpy(kce->extract_filename, PERF_KCORE_EXTRACT);
	if (kcore__init(&extract, kce->extract_filename, kcore.elfclass, true))
		goto out_kcore_close;

	if (kcore__copy_hdr(&kcore, &extract, count))
		goto out_extract_close;

	if (kcore__add_phdr(&extract, idx, offset, kce->addr, kce->len))
		goto out_extract_close;

	sz = kcore__write(&extract);
	if (sz < 0 || sz > offset)
		goto out_extract_close;

	if (copy_bytes(kcore.fd, kce->offs, extract.fd, offset, kce->len))
		goto out_extract_close;

	err = 0;

out_extract_close:
	kcore__close(&extract);
	if (err)
		unlink(kce->extract_filename);
out_kcore_close:
	kcore__close(&kcore);

	return err;
}