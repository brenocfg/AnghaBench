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
struct nvmf_host {int /*<<< orphan*/  list; int /*<<< orphan*/  nqn; int /*<<< orphan*/  id; int /*<<< orphan*/  ref; } ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  NVMF_NQN_SIZE ; 
 struct nvmf_host* kmalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kref_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  list_add_tail (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  nvmf_hosts ; 
 int /*<<< orphan*/  nvmf_hosts_mutex ; 
 int /*<<< orphan*/  snprintf (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  uuid_gen (int /*<<< orphan*/ *) ; 

__attribute__((used)) static struct nvmf_host *nvmf_host_default(void)
{
	struct nvmf_host *host;

	host = kmalloc(sizeof(*host), GFP_KERNEL);
	if (!host)
		return NULL;

	kref_init(&host->ref);
	uuid_gen(&host->id);
	snprintf(host->nqn, NVMF_NQN_SIZE,
		"nqn.2014-08.org.nvmexpress:uuid:%pUb", &host->id);

	mutex_lock(&nvmf_hosts_mutex);
	list_add_tail(&host->list, &nvmf_hosts);
	mutex_unlock(&nvmf_hosts_mutex);

	return host;
}