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
struct rsc_hdr {int dummy; } ;
struct entry_header {int /*<<< orphan*/  len; } ;

/* Variables and functions */
 int cmd_db_get_header (char const*,struct entry_header*,struct rsc_hdr*) ; 
 size_t le16_to_cpu (int /*<<< orphan*/ ) ; 

size_t cmd_db_read_aux_data_len(const char *id)
{
	int ret;
	struct entry_header ent;
	struct rsc_hdr rsc_hdr;

	ret = cmd_db_get_header(id, &ent, &rsc_hdr);

	return ret < 0 ? 0 : le16_to_cpu(ent.len);
}