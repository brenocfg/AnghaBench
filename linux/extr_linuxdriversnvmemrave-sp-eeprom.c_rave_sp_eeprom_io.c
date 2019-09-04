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
typedef  int u8 ;
typedef  int u16 ;
struct rave_sp_eeprom_page {int type; int /*<<< orphan*/  success; int /*<<< orphan*/  data; } ;
struct rave_sp_eeprom {unsigned int const header_size; int address; int /*<<< orphan*/  sp; } ;
typedef  enum rave_sp_eeprom_access_type { ____Placeholder_rave_sp_eeprom_access_type } rave_sp_eeprom_access_type ;
typedef  int /*<<< orphan*/  cmd ;

/* Variables and functions */
 int EINVAL ; 
 int EIO ; 
 int EPROTO ; 
 int /*<<< orphan*/  RAVE_SP_EEPROM_HEADER_MAX ; 
 int RAVE_SP_EEPROM_WRITE ; 
 scalar_t__ WARN_ON (int) ; 
 int /*<<< orphan*/  memcpy (int*,int /*<<< orphan*/ ,unsigned int const) ; 
 int rave_sp_exec (int /*<<< orphan*/ ,int*,unsigned int const,struct rave_sp_eeprom_page*,unsigned int const) ; 

__attribute__((used)) static int rave_sp_eeprom_io(struct rave_sp_eeprom *eeprom,
			     enum rave_sp_eeprom_access_type type,
			     u16 idx,
			     struct rave_sp_eeprom_page *page)
{
	const bool is_write = type == RAVE_SP_EEPROM_WRITE;
	const unsigned int data_size = is_write ? sizeof(page->data) : 0;
	const unsigned int cmd_size = eeprom->header_size + data_size;
	const unsigned int rsp_size =
		is_write ? sizeof(*page) - sizeof(page->data) : sizeof(*page);
	unsigned int offset = 0;
	u8 cmd[RAVE_SP_EEPROM_HEADER_MAX + sizeof(page->data)];
	int ret;

	if (WARN_ON(cmd_size > sizeof(cmd)))
		return -EINVAL;

	cmd[offset++] = eeprom->address;
	cmd[offset++] = 0;
	cmd[offset++] = type;
	cmd[offset++] = idx;

	/*
	 * If there's still room in this command's header it means we
	 * are talkin to EEPROM that uses 16-bit page numbers and we
	 * have to specify index's MSB in payload as well.
	 */
	if (offset < eeprom->header_size)
		cmd[offset++] = idx >> 8;
	/*
	 * Copy our data to write to command buffer first. In case of
	 * a read data_size should be zero and memcpy would become a
	 * no-op
	 */
	memcpy(&cmd[offset], page->data, data_size);

	ret = rave_sp_exec(eeprom->sp, cmd, cmd_size, page, rsp_size);
	if (ret)
		return ret;

	if (page->type != type)
		return -EPROTO;

	if (!page->success)
		return -EIO;

	return 0;
}