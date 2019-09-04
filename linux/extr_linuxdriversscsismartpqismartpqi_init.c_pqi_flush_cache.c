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
struct pqi_raid_path_request {int /*<<< orphan*/  sg_descriptors; int /*<<< orphan*/  header; } ;
struct pqi_ctrl_info {int /*<<< orphan*/  pci_dev; } ;
struct bmic_flush_cache {int shutdown_event; } ;
typedef  enum bmic_flush_cache_shutdown_event { ____Placeholder_bmic_flush_cache_shutdown_event } bmic_flush_cache_shutdown_event ;

/* Variables and functions */
 int ENOMEM ; 
 int ENXIO ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  NO_TIMEOUT ; 
 int /*<<< orphan*/  RAID_CTLR_LUNID ; 
 int /*<<< orphan*/  SA_FLUSH_CACHE ; 
 int /*<<< orphan*/  kfree (struct bmic_flush_cache*) ; 
 struct bmic_flush_cache* kzalloc (int,int /*<<< orphan*/ ) ; 
 int pqi_build_raid_path_request (struct pqi_ctrl_info*,struct pqi_raid_path_request*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct bmic_flush_cache*,int,int /*<<< orphan*/ ,int*) ; 
 scalar_t__ pqi_ctrl_offline (struct pqi_ctrl_info*) ; 
 int /*<<< orphan*/  pqi_pci_unmap (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int) ; 
 int pqi_submit_raid_request_synchronous (struct pqi_ctrl_info*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int pqi_flush_cache(struct pqi_ctrl_info *ctrl_info,
	enum bmic_flush_cache_shutdown_event shutdown_event)
{
	int rc;
	struct pqi_raid_path_request request;
	int pci_direction;
	struct bmic_flush_cache *flush_cache;

	/*
	 * Don't bother trying to flush the cache if the controller is
	 * locked up.
	 */
	if (pqi_ctrl_offline(ctrl_info))
		return -ENXIO;

	flush_cache = kzalloc(sizeof(*flush_cache), GFP_KERNEL);
	if (!flush_cache)
		return -ENOMEM;

	flush_cache->shutdown_event = shutdown_event;

	rc = pqi_build_raid_path_request(ctrl_info, &request,
		SA_FLUSH_CACHE, RAID_CTLR_LUNID, flush_cache,
		sizeof(*flush_cache), 0, &pci_direction);
	if (rc)
		goto out;

	rc = pqi_submit_raid_request_synchronous(ctrl_info, &request.header,
		0, NULL, NO_TIMEOUT);

	pqi_pci_unmap(ctrl_info->pci_dev, request.sg_descriptors, 1,
		pci_direction);

out:
	kfree(flush_cache);

	return rc;
}