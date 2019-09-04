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
typedef  int u32 ;
struct TYPE_2__ {int /*<<< orphan*/ * data; int /*<<< orphan*/  boot_size; int /*<<< orphan*/  init_data_size; int /*<<< orphan*/  init_size; int /*<<< orphan*/  data_size; int /*<<< orphan*/  inst_size; } ;
struct il_ucode_header {TYPE_1__ v1; int /*<<< orphan*/  ver; } ;
struct il_priv {void* ucode_ver; } ;
struct il4965_firmware_pieces {int inst_size; int data_size; int init_size; int init_data_size; int boot_size; int /*<<< orphan*/  const* boot; int /*<<< orphan*/  const* init_data; int /*<<< orphan*/  const* init; int /*<<< orphan*/  const* data; int /*<<< orphan*/  const* inst; } ;
struct firmware {int size; scalar_t__ data; } ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  IL_ERR (char*,...) ; 
 int IL_UCODE_API (void*) ; 
 void* le32_to_cpu (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
il4965_load_firmware(struct il_priv *il, const struct firmware *ucode_raw,
		     struct il4965_firmware_pieces *pieces)
{
	struct il_ucode_header *ucode = (void *)ucode_raw->data;
	u32 api_ver, hdr_size;
	const u8 *src;

	il->ucode_ver = le32_to_cpu(ucode->ver);
	api_ver = IL_UCODE_API(il->ucode_ver);

	switch (api_ver) {
	default:
	case 0:
	case 1:
	case 2:
		hdr_size = 24;
		if (ucode_raw->size < hdr_size) {
			IL_ERR("File size too small!\n");
			return -EINVAL;
		}
		pieces->inst_size = le32_to_cpu(ucode->v1.inst_size);
		pieces->data_size = le32_to_cpu(ucode->v1.data_size);
		pieces->init_size = le32_to_cpu(ucode->v1.init_size);
		pieces->init_data_size = le32_to_cpu(ucode->v1.init_data_size);
		pieces->boot_size = le32_to_cpu(ucode->v1.boot_size);
		src = ucode->v1.data;
		break;
	}

	/* Verify size of file vs. image size info in file's header */
	if (ucode_raw->size !=
	    hdr_size + pieces->inst_size + pieces->data_size +
	    pieces->init_size + pieces->init_data_size + pieces->boot_size) {

		IL_ERR("uCode file size %d does not match expected size\n",
		       (int)ucode_raw->size);
		return -EINVAL;
	}

	pieces->inst = src;
	src += pieces->inst_size;
	pieces->data = src;
	src += pieces->data_size;
	pieces->init = src;
	src += pieces->init_size;
	pieces->init_data = src;
	src += pieces->init_data_size;
	pieces->boot = src;
	src += pieces->boot_size;

	return 0;
}