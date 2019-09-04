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
typedef  int /*<<< orphan*/  umode_t ;
struct cifs_sid {int num_subauth; int /*<<< orphan*/ * sub_auth; int /*<<< orphan*/ * authority; int /*<<< orphan*/  revision; } ;
struct TYPE_2__ {int num_subauth; int /*<<< orphan*/ * sub_auth; int /*<<< orphan*/ * authority; int /*<<< orphan*/  revision; } ;
struct cifs_ace {int flags; int /*<<< orphan*/  size; TYPE_1__ sid; int /*<<< orphan*/  access_req; int /*<<< orphan*/  type; } ;
typedef  int /*<<< orphan*/  __u64 ;
typedef  scalar_t__ __u32 ;
typedef  int __u16 ;

/* Variables and functions */
 int /*<<< orphan*/  ACCESS_ALLOWED ; 
 int NUM_AUTHS ; 
 scalar_t__ SET_MINIMUM_RIGHTS ; 
 int /*<<< orphan*/  cpu_to_le16 (int) ; 
 int /*<<< orphan*/  cpu_to_le32 (scalar_t__) ; 
 int /*<<< orphan*/  mode_to_access_flags (int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__*) ; 

__attribute__((used)) static __u16 fill_ace_for_sid(struct cifs_ace *pntace,
			const struct cifs_sid *psid, __u64 nmode, umode_t bits)
{
	int i;
	__u16 size = 0;
	__u32 access_req = 0;

	pntace->type = ACCESS_ALLOWED;
	pntace->flags = 0x0;
	mode_to_access_flags(nmode, bits, &access_req);
	if (!access_req)
		access_req = SET_MINIMUM_RIGHTS;
	pntace->access_req = cpu_to_le32(access_req);

	pntace->sid.revision = psid->revision;
	pntace->sid.num_subauth = psid->num_subauth;
	for (i = 0; i < NUM_AUTHS; i++)
		pntace->sid.authority[i] = psid->authority[i];
	for (i = 0; i < psid->num_subauth; i++)
		pntace->sid.sub_auth[i] = psid->sub_auth[i];

	size = 1 + 1 + 2 + 4 + 1 + 1 + 6 + (psid->num_subauth * 4);
	pntace->size = cpu_to_le16(size);

	return size;
}