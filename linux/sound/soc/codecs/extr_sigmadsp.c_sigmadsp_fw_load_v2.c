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
struct sigmadsp {int /*<<< orphan*/  dev; } ;
struct sigma_fw_chunk {int /*<<< orphan*/  tag; int /*<<< orphan*/  length; } ;
struct sigma_firmware_header {int dummy; } ;
struct firmware {int size; scalar_t__ data; } ;
typedef  int /*<<< orphan*/  __le32 ;

/* Variables and functions */
 scalar_t__ ALIGN (unsigned int,int) ; 
 int EINVAL ; 
#define  SIGMA_FW_CHUNK_TYPE_CONTROL 130 
#define  SIGMA_FW_CHUNK_TYPE_DATA 129 
#define  SIGMA_FW_CHUNK_TYPE_SAMPLERATES 128 
 int /*<<< orphan*/  dev_warn (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int le32_to_cpu (int /*<<< orphan*/ ) ; 
 int sigma_fw_load_control (struct sigmadsp*,struct sigma_fw_chunk*,unsigned int) ; 
 int sigma_fw_load_data (struct sigmadsp*,struct sigma_fw_chunk*,unsigned int) ; 
 int sigma_fw_load_samplerates (struct sigmadsp*,struct sigma_fw_chunk*,unsigned int) ; 

__attribute__((used)) static int sigmadsp_fw_load_v2(struct sigmadsp *sigmadsp,
	const struct firmware *fw)
{
	struct sigma_fw_chunk *chunk;
	unsigned int length, pos;
	int ret;

	/*
	 * Make sure that there is at least one chunk to avoid integer
	 * underflows later on. Empty firmware is still valid though.
	 */
	if (fw->size < sizeof(*chunk) + sizeof(struct sigma_firmware_header))
		return 0;

	pos = sizeof(struct sigma_firmware_header);

	while (pos < fw->size - sizeof(*chunk)) {
		chunk = (struct sigma_fw_chunk *)(fw->data + pos);

		length = le32_to_cpu(chunk->length);

		if (length > fw->size - pos || length < sizeof(*chunk))
			return -EINVAL;

		switch (le32_to_cpu(chunk->tag)) {
		case SIGMA_FW_CHUNK_TYPE_DATA:
			ret = sigma_fw_load_data(sigmadsp, chunk, length);
			break;
		case SIGMA_FW_CHUNK_TYPE_CONTROL:
			ret = sigma_fw_load_control(sigmadsp, chunk, length);
			break;
		case SIGMA_FW_CHUNK_TYPE_SAMPLERATES:
			ret = sigma_fw_load_samplerates(sigmadsp, chunk, length);
			break;
		default:
			dev_warn(sigmadsp->dev, "Unknown chunk type: %d\n",
				chunk->tag);
			ret = 0;
			break;
		}

		if (ret)
			return ret;

		/*
		 * This can not overflow since if length is larger than the
		 * maximum firmware size (0x4000000) we'll error out earilier.
		 */
		pos += ALIGN(length, sizeof(__le32));
	}

	return 0;
}