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
struct pstore_record {scalar_t__ size; struct pstore_record* buf; } ;
struct pstore_info {scalar_t__ (* read ) (struct pstore_record*) ;int /*<<< orphan*/  name; int /*<<< orphan*/  read_mutex; int /*<<< orphan*/  (* close ) (struct pstore_info*) ;scalar_t__ (* open ) (struct pstore_info*) ;} ;
struct dentry {int dummy; } ;

/* Variables and functions */
 int EEXIST ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  decompress_record (struct pstore_record*) ; 
 int /*<<< orphan*/  kfree (struct pstore_record*) ; 
 struct pstore_record* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pr_err (char*,...) ; 
 int /*<<< orphan*/  pr_warn (char*,int,int /*<<< orphan*/ ) ; 
 int pstore_mkfile (struct dentry*,struct pstore_record*) ; 
 int /*<<< orphan*/  pstore_record_init (struct pstore_record*,struct pstore_info*) ; 
 scalar_t__ stub1 (struct pstore_info*) ; 
 scalar_t__ stub2 (struct pstore_record*) ; 
 int /*<<< orphan*/  stub3 (struct pstore_info*) ; 

void pstore_get_backend_records(struct pstore_info *psi,
				struct dentry *root, int quiet)
{
	int failed = 0;
	unsigned int stop_loop = 65536;

	if (!psi || !root)
		return;

	mutex_lock(&psi->read_mutex);
	if (psi->open && psi->open(psi))
		goto out;

	/*
	 * Backend callback read() allocates record.buf. decompress_record()
	 * may reallocate record.buf. On success, pstore_mkfile() will keep
	 * the record.buf, so free it only on failure.
	 */
	for (; stop_loop; stop_loop--) {
		struct pstore_record *record;
		int rc;

		record = kzalloc(sizeof(*record), GFP_KERNEL);
		if (!record) {
			pr_err("out of memory creating record\n");
			break;
		}
		pstore_record_init(record, psi);

		record->size = psi->read(record);

		/* No more records left in backend? */
		if (record->size <= 0) {
			kfree(record);
			break;
		}

		decompress_record(record);
		rc = pstore_mkfile(root, record);
		if (rc) {
			/* pstore_mkfile() did not take record, so free it. */
			kfree(record->buf);
			kfree(record);
			if (rc != -EEXIST || !quiet)
				failed++;
		}
	}
	if (psi->close)
		psi->close(psi);
out:
	mutex_unlock(&psi->read_mutex);

	if (failed)
		pr_warn("failed to create %d record(s) from '%s'\n",
			failed, psi->name);
	if (!stop_loop)
		pr_err("looping? Too many records seen from '%s'\n",
			psi->name);
}