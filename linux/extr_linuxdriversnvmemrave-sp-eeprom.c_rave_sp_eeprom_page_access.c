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
typedef  int /*<<< orphan*/  u8 ;
struct rave_sp_eeprom_page {int /*<<< orphan*/ * data; } ;
struct rave_sp_eeprom {int dummy; } ;
typedef  enum rave_sp_eeprom_access_type { ____Placeholder_rave_sp_eeprom_access_type } rave_sp_eeprom_access_type ;

/* Variables and functions */
 int EINVAL ; 
 unsigned int RAVE_SP_EEPROM_PAGE_SIZE ; 
 int RAVE_SP_EEPROM_READ ; 
 int RAVE_SP_EEPROM_WRITE ; 
 scalar_t__ WARN_ON (int) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,int /*<<< orphan*/ *,size_t) ; 
 int rave_sp_eeprom_io (struct rave_sp_eeprom*,int,unsigned int const,struct rave_sp_eeprom_page*) ; 

__attribute__((used)) static int
rave_sp_eeprom_page_access(struct rave_sp_eeprom *eeprom,
			   enum rave_sp_eeprom_access_type type,
			   unsigned int offset, u8 *data,
			   size_t data_len)
{
	const unsigned int page_offset = offset % RAVE_SP_EEPROM_PAGE_SIZE;
	const unsigned int page_nr     = offset / RAVE_SP_EEPROM_PAGE_SIZE;
	struct rave_sp_eeprom_page page;
	int ret;

	/*
	 * This function will not work if data access we've been asked
	 * to do is crossing EEPROM page boundary. Normally this
	 * should never happen and getting here would indicate a bug
	 * in the code.
	 */
	if (WARN_ON(data_len > sizeof(page.data) - page_offset))
		return -EINVAL;

	if (type == RAVE_SP_EEPROM_WRITE) {
		/*
		 * If doing a partial write we need to do a read first
		 * to fill the rest of the page with correct data.
		 */
		if (data_len < RAVE_SP_EEPROM_PAGE_SIZE) {
			ret = rave_sp_eeprom_io(eeprom, RAVE_SP_EEPROM_READ,
						page_nr, &page);
			if (ret)
				return ret;
		}

		memcpy(&page.data[page_offset], data, data_len);
	}

	ret = rave_sp_eeprom_io(eeprom, type, page_nr, &page);
	if (ret)
		return ret;

	/*
	 * Since we receive the result of the read via 'page.data'
	 * buffer we need to copy that to 'data'
	 */
	if (type == RAVE_SP_EEPROM_READ)
		memcpy(data, &page.data[page_offset], data_len);

	return 0;
}