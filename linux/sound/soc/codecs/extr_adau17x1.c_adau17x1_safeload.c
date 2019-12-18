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
typedef  int /*<<< orphan*/  const uint8_t ;
struct sigmadsp {int /*<<< orphan*/  control_data; } ;

/* Variables and functions */
 int /*<<< orphan*/  ADAU17X1_SAFELOAD_DATA ; 
 int ADAU17X1_SAFELOAD_DATA_SIZE ; 
 int /*<<< orphan*/  ADAU17X1_SAFELOAD_TARGET_ADDRESS ; 
 int /*<<< orphan*/  ADAU17X1_SAFELOAD_TRIGGER ; 
 int ADAU17X1_WORD_SIZE ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/  const*,int /*<<< orphan*/  const*,size_t) ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/  const*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  put_unaligned_be32 (unsigned int,int /*<<< orphan*/  const*) ; 
 int regmap_raw_write (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/  const*,int) ; 

__attribute__((used)) static int adau17x1_safeload(struct sigmadsp *sigmadsp, unsigned int addr,
	const uint8_t bytes[], size_t len)
{
	uint8_t buf[ADAU17X1_WORD_SIZE];
	uint8_t data[ADAU17X1_SAFELOAD_DATA_SIZE];
	unsigned int addr_offset;
	unsigned int nbr_words;
	int ret;

	/* write data to safeload addresses. Check if len is not a multiple of
	 * 4 bytes, if so we need to zero pad.
	 */
	nbr_words = len / ADAU17X1_WORD_SIZE;
	if ((len - nbr_words * ADAU17X1_WORD_SIZE) == 0) {
		ret = regmap_raw_write(sigmadsp->control_data,
			ADAU17X1_SAFELOAD_DATA, bytes, len);
	} else {
		nbr_words++;
		memset(data, 0, ADAU17X1_SAFELOAD_DATA_SIZE);
		memcpy(data, bytes, len);
		ret = regmap_raw_write(sigmadsp->control_data,
			ADAU17X1_SAFELOAD_DATA, data,
			nbr_words * ADAU17X1_WORD_SIZE);
	}

	if (ret < 0)
		return ret;

	/* Write target address, target address is offset by 1 */
	addr_offset = addr - 1;
	put_unaligned_be32(addr_offset, buf);
	ret = regmap_raw_write(sigmadsp->control_data,
		ADAU17X1_SAFELOAD_TARGET_ADDRESS, buf, ADAU17X1_WORD_SIZE);
	if (ret < 0)
		return ret;

	/* write nbr of words to trigger address */
	put_unaligned_be32(nbr_words, buf);
	ret = regmap_raw_write(sigmadsp->control_data,
		ADAU17X1_SAFELOAD_TRIGGER, buf, ADAU17X1_WORD_SIZE);
	if (ret < 0)
		return ret;

	return 0;
}