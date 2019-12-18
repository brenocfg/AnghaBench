#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int /*<<< orphan*/  ecc_size; } ;
struct ramoops_platform_data {size_t mem_size; size_t record_size; size_t console_size; size_t ftrace_size; size_t pmsg_size; int flags; int /*<<< orphan*/  dump_oops; scalar_t__ mem_address; TYPE_1__ ecc_info; int /*<<< orphan*/  mem_type; } ;
struct TYPE_6__ {int flags; scalar_t__ bufsize; int /*<<< orphan*/  buf; struct ramoops_context* data; } ;
struct ramoops_context {int max_dump_cnt; size_t size; size_t record_size; size_t console_size; size_t ftrace_size; size_t pmsg_size; int flags; int max_ftrace_cnt; int /*<<< orphan*/  cprz; int /*<<< orphan*/  mprz; TYPE_3__ pstore; TYPE_1__ ecc_info; scalar_t__ phys_addr; TYPE_2__** dprzs; TYPE_2__** fprzs; int /*<<< orphan*/  dump_oops; int /*<<< orphan*/  memtype; } ;
struct device {struct ramoops_platform_data* platform_data; } ;
struct platform_device {struct device dev; } ;
typedef  scalar_t__ phys_addr_t ;
struct TYPE_5__ {scalar_t__ buffer_size; } ;

/* Variables and functions */
 int EINVAL ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  LINUX_VERSION_CODE ; 
 int /*<<< orphan*/  PRZ_FLAG_NO_LOCK ; 
 int PSTORE_FLAGS_CONSOLE ; 
 int PSTORE_FLAGS_DMESG ; 
 int PSTORE_FLAGS_FTRACE ; 
 int PSTORE_FLAGS_PMSG ; 
 int RAMOOPS_FLAG_FTRACE_PER_CPU ; 
 scalar_t__ dev_of_node (struct device*) ; 
 int /*<<< orphan*/  dump_oops ; 
 int /*<<< orphan*/  is_power_of_2 (size_t) ; 
 int /*<<< orphan*/  kfree (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kzalloc (scalar_t__,int /*<<< orphan*/ ) ; 
 scalar_t__ mem_address ; 
 size_t mem_size ; 
 int /*<<< orphan*/  memset (struct ramoops_platform_data*,int /*<<< orphan*/ ,int) ; 
 int nr_cpu_ids ; 
 struct ramoops_context oops_cxt ; 
 int /*<<< orphan*/  persistent_ram_free (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pr_err (char*) ; 
 int /*<<< orphan*/  pr_info (char*,size_t,unsigned long long,int /*<<< orphan*/ ) ; 
 int pstore_register (TYPE_3__*) ; 
 size_t ramoops_console_size ; 
 int /*<<< orphan*/  ramoops_free_przs (struct ramoops_context*) ; 
 size_t ramoops_ftrace_size ; 
 int ramoops_init_prz (char*,struct device*,struct ramoops_context*,int /*<<< orphan*/ *,scalar_t__*,size_t,int /*<<< orphan*/ ) ; 
 int ramoops_init_przs (char*,struct device*,struct ramoops_context*,TYPE_2__***,scalar_t__*,size_t,int,int*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int ramoops_parse_dt (struct platform_device*,struct ramoops_platform_data*) ; 
 size_t ramoops_pmsg_size ; 
 size_t record_size ; 
 void* rounddown_pow_of_two (size_t) ; 

__attribute__((used)) static int ramoops_probe(struct platform_device *pdev)
{
	struct device *dev = &pdev->dev;
	struct ramoops_platform_data *pdata = dev->platform_data;
	struct ramoops_platform_data pdata_local;
	struct ramoops_context *cxt = &oops_cxt;
	size_t dump_mem_sz;
	phys_addr_t paddr;
	int err = -EINVAL;

	/*
	 * Only a single ramoops area allowed at a time, so fail extra
	 * probes.
	 */
	if (cxt->max_dump_cnt) {
		pr_err("already initialized\n");
		goto fail_out;
	}

	if (dev_of_node(dev) && !pdata) {
		pdata = &pdata_local;
		memset(pdata, 0, sizeof(*pdata));

		err = ramoops_parse_dt(pdev, pdata);
		if (err < 0)
			goto fail_out;
	}

	/* Make sure we didn't get bogus platform data pointer. */
	if (!pdata) {
		pr_err("NULL platform data\n");
		goto fail_out;
	}

	if (!pdata->mem_size || (!pdata->record_size && !pdata->console_size &&
			!pdata->ftrace_size && !pdata->pmsg_size)) {
		pr_err("The memory size and the record/console size must be "
			"non-zero\n");
		goto fail_out;
	}

	if (pdata->record_size && !is_power_of_2(pdata->record_size))
		pdata->record_size = rounddown_pow_of_two(pdata->record_size);
	if (pdata->console_size && !is_power_of_2(pdata->console_size))
		pdata->console_size = rounddown_pow_of_two(pdata->console_size);
	if (pdata->ftrace_size && !is_power_of_2(pdata->ftrace_size))
		pdata->ftrace_size = rounddown_pow_of_two(pdata->ftrace_size);
	if (pdata->pmsg_size && !is_power_of_2(pdata->pmsg_size))
		pdata->pmsg_size = rounddown_pow_of_two(pdata->pmsg_size);

	cxt->size = pdata->mem_size;
	cxt->phys_addr = pdata->mem_address;
	cxt->memtype = pdata->mem_type;
	cxt->record_size = pdata->record_size;
	cxt->console_size = pdata->console_size;
	cxt->ftrace_size = pdata->ftrace_size;
	cxt->pmsg_size = pdata->pmsg_size;
	cxt->dump_oops = pdata->dump_oops;
	cxt->flags = pdata->flags;
	cxt->ecc_info = pdata->ecc_info;

	paddr = cxt->phys_addr;

	dump_mem_sz = cxt->size - cxt->console_size - cxt->ftrace_size
			- cxt->pmsg_size;
	err = ramoops_init_przs("dmesg", dev, cxt, &cxt->dprzs, &paddr,
				dump_mem_sz, cxt->record_size,
				&cxt->max_dump_cnt, 0, 0);
	if (err)
		goto fail_out;

	err = ramoops_init_prz("console", dev, cxt, &cxt->cprz, &paddr,
			       cxt->console_size, 0);
	if (err)
		goto fail_init_cprz;

	cxt->max_ftrace_cnt = (cxt->flags & RAMOOPS_FLAG_FTRACE_PER_CPU)
				? nr_cpu_ids
				: 1;
	err = ramoops_init_przs("ftrace", dev, cxt, &cxt->fprzs, &paddr,
				cxt->ftrace_size, -1,
				&cxt->max_ftrace_cnt, LINUX_VERSION_CODE,
				(cxt->flags & RAMOOPS_FLAG_FTRACE_PER_CPU)
					? PRZ_FLAG_NO_LOCK : 0);
	if (err)
		goto fail_init_fprz;

	err = ramoops_init_prz("pmsg", dev, cxt, &cxt->mprz, &paddr,
				cxt->pmsg_size, 0);
	if (err)
		goto fail_init_mprz;

	cxt->pstore.data = cxt;
	/*
	 * Prepare frontend flags based on which areas are initialized.
	 * For ramoops_init_przs() cases, the "max count" variable tells
	 * if there are regions present. For ramoops_init_prz() cases,
	 * the single region size is how to check.
	 */
	cxt->pstore.flags = 0;
	if (cxt->max_dump_cnt)
		cxt->pstore.flags |= PSTORE_FLAGS_DMESG;
	if (cxt->console_size)
		cxt->pstore.flags |= PSTORE_FLAGS_CONSOLE;
	if (cxt->max_ftrace_cnt)
		cxt->pstore.flags |= PSTORE_FLAGS_FTRACE;
	if (cxt->pmsg_size)
		cxt->pstore.flags |= PSTORE_FLAGS_PMSG;

	/*
	 * Since bufsize is only used for dmesg crash dumps, it
	 * must match the size of the dprz record (after PRZ header
	 * and ECC bytes have been accounted for).
	 */
	if (cxt->pstore.flags & PSTORE_FLAGS_DMESG) {
		cxt->pstore.bufsize = cxt->dprzs[0]->buffer_size;
		cxt->pstore.buf = kzalloc(cxt->pstore.bufsize, GFP_KERNEL);
		if (!cxt->pstore.buf) {
			pr_err("cannot allocate pstore crash dump buffer\n");
			err = -ENOMEM;
			goto fail_clear;
		}
	}

	err = pstore_register(&cxt->pstore);
	if (err) {
		pr_err("registering with pstore failed\n");
		goto fail_buf;
	}

	/*
	 * Update the module parameter variables as well so they are visible
	 * through /sys/module/ramoops/parameters/
	 */
	mem_size = pdata->mem_size;
	mem_address = pdata->mem_address;
	record_size = pdata->record_size;
	dump_oops = pdata->dump_oops;
	ramoops_console_size = pdata->console_size;
	ramoops_pmsg_size = pdata->pmsg_size;
	ramoops_ftrace_size = pdata->ftrace_size;

	pr_info("using 0x%lx@0x%llx, ecc: %d\n",
		cxt->size, (unsigned long long)cxt->phys_addr,
		cxt->ecc_info.ecc_size);

	return 0;

fail_buf:
	kfree(cxt->pstore.buf);
fail_clear:
	cxt->pstore.bufsize = 0;
	persistent_ram_free(cxt->mprz);
fail_init_mprz:
fail_init_fprz:
	persistent_ram_free(cxt->cprz);
fail_init_cprz:
	ramoops_free_przs(cxt);
fail_out:
	return err;
}