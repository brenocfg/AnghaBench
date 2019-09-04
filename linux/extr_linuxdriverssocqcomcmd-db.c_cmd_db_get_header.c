#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u8 ;
struct rsc_hdr {int /*<<< orphan*/  cnt; int /*<<< orphan*/  id; int /*<<< orphan*/  slv_id; } ;
struct entry_header {int /*<<< orphan*/  cnt; int /*<<< orphan*/  id; int /*<<< orphan*/  slv_id; } ;
typedef  int /*<<< orphan*/  query ;
struct TYPE_2__ {struct rsc_hdr* header; } ;

/* Variables and functions */
 int EINVAL ; 
 int ENODEV ; 
 int MAX_SLV_ID ; 
 TYPE_1__* cmd_db_header ; 
 int cmd_db_ready () ; 
 int le16_to_cpu (int /*<<< orphan*/ ) ; 
 scalar_t__ memcmp (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  memcpy (struct rsc_hdr*,struct rsc_hdr*,int) ; 
 struct rsc_hdr* rsc_to_entry_header (struct rsc_hdr*) ; 
 int /*<<< orphan*/  strncpy (int /*<<< orphan*/ *,char const*,int) ; 

__attribute__((used)) static int cmd_db_get_header(const char *id, struct entry_header *eh,
			     struct rsc_hdr *rh)
{
	struct rsc_hdr *rsc_hdr;
	struct entry_header *ent;
	int ret, i, j;
	u8 query[8];

	ret = cmd_db_ready();
	if (ret)
		return ret;

	if (!eh || !rh)
		return -EINVAL;

	/* Pad out query string to same length as in DB */
	strncpy(query, id, sizeof(query));

	for (i = 0; i < MAX_SLV_ID; i++) {
		rsc_hdr = &cmd_db_header->header[i];
		if (!rsc_hdr->slv_id)
			break;

		ent = rsc_to_entry_header(rsc_hdr);
		for (j = 0; j < le16_to_cpu(rsc_hdr->cnt); j++, ent++) {
			if (memcmp(ent->id, query, sizeof(ent->id)) == 0)
				break;
		}

		if (j < le16_to_cpu(rsc_hdr->cnt)) {
			memcpy(eh, ent, sizeof(*ent));
			memcpy(rh, rsc_hdr, sizeof(*rh));
			return 0;
		}
	}

	return -ENODEV;
}