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
struct nfc_llc_ops {int dummy; } ;
struct nfc_llc_engine {int /*<<< orphan*/  entry; struct nfc_llc_ops* ops; int /*<<< orphan*/ * name; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  INIT_LIST_HEAD (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  kfree (struct nfc_llc_engine*) ; 
 int /*<<< orphan*/ * kstrdup (char const*,int /*<<< orphan*/ ) ; 
 struct nfc_llc_engine* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  list_add_tail (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  llc_engines ; 

int nfc_llc_register(const char *name, struct nfc_llc_ops *ops)
{
	struct nfc_llc_engine *llc_engine;

	llc_engine = kzalloc(sizeof(struct nfc_llc_engine), GFP_KERNEL);
	if (llc_engine == NULL)
		return -ENOMEM;

	llc_engine->name = kstrdup(name, GFP_KERNEL);
	if (llc_engine->name == NULL) {
		kfree(llc_engine);
		return -ENOMEM;
	}
	llc_engine->ops = ops;

	INIT_LIST_HEAD(&llc_engine->entry);
	list_add_tail(&llc_engine->entry, &llc_engines);

	return 0;
}