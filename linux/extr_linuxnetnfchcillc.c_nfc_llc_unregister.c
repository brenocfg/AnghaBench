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
struct nfc_llc_engine {struct nfc_llc_engine* name; int /*<<< orphan*/  entry; } ;

/* Variables and functions */
 int /*<<< orphan*/  kfree (struct nfc_llc_engine*) ; 
 int /*<<< orphan*/  list_del (int /*<<< orphan*/ *) ; 
 struct nfc_llc_engine* nfc_llc_name_to_engine (char const*) ; 

void nfc_llc_unregister(const char *name)
{
	struct nfc_llc_engine *llc_engine;

	llc_engine = nfc_llc_name_to_engine(name);
	if (llc_engine == NULL)
		return;

	list_del(&llc_engine->entry);
	kfree(llc_engine->name);
	kfree(llc_engine);
}