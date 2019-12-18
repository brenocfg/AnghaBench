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
typedef  int /*<<< orphan*/  const u8 ;
struct fwdb_header {scalar_t__ magic; scalar_t__ version; struct fwdb_country* country; } ;
struct fwdb_country {int /*<<< orphan*/  coll_ptr; } ;

/* Variables and functions */
 int /*<<< orphan*/  FWDB_MAGIC ; 
 int /*<<< orphan*/  FWDB_VERSION ; 
 scalar_t__ cpu_to_be32 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  regdb_has_valid_signature (int /*<<< orphan*/  const*,unsigned int) ; 
 int /*<<< orphan*/  valid_country (int /*<<< orphan*/  const*,unsigned int,struct fwdb_country const*) ; 

__attribute__((used)) static bool valid_regdb(const u8 *data, unsigned int size)
{
	const struct fwdb_header *hdr = (void *)data;
	const struct fwdb_country *country;

	if (size < sizeof(*hdr))
		return false;

	if (hdr->magic != cpu_to_be32(FWDB_MAGIC))
		return false;

	if (hdr->version != cpu_to_be32(FWDB_VERSION))
		return false;

	if (!regdb_has_valid_signature(data, size))
		return false;

	country = &hdr->country[0];
	while ((u8 *)(country + 1) <= data + size) {
		if (!country->coll_ptr)
			break;
		if (!valid_country(data, size, country))
			return false;
		country++;
	}

	return true;
}