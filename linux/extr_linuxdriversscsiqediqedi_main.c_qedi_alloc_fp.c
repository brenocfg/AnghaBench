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
struct qedi_fastpath {int dummy; } ;
struct qedi_ctx {int /*<<< orphan*/  dbg_ctx; void* sb_array; void* fp_array; } ;
struct qed_sb_info {int dummy; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  MIN_NUM_CPUS_MSIX (struct qedi_ctx*) ; 
 int /*<<< orphan*/  QEDI_ERR (int /*<<< orphan*/ *,char*) ; 
 void* kcalloc (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  qedi_free_fp (struct qedi_ctx*) ; 

__attribute__((used)) static int qedi_alloc_fp(struct qedi_ctx *qedi)
{
	int ret = 0;

	qedi->fp_array = kcalloc(MIN_NUM_CPUS_MSIX(qedi),
				 sizeof(struct qedi_fastpath), GFP_KERNEL);
	if (!qedi->fp_array) {
		QEDI_ERR(&qedi->dbg_ctx,
			 "fastpath fp array allocation failed.\n");
		return -ENOMEM;
	}

	qedi->sb_array = kcalloc(MIN_NUM_CPUS_MSIX(qedi),
				 sizeof(struct qed_sb_info), GFP_KERNEL);
	if (!qedi->sb_array) {
		QEDI_ERR(&qedi->dbg_ctx,
			 "fastpath sb array allocation failed.\n");
		ret = -ENOMEM;
		goto free_fp;
	}

	return ret;

free_fp:
	qedi_free_fp(qedi);
	return ret;
}