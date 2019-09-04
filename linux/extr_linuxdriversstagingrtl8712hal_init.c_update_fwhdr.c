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
struct fw_hdr {void* fw_priv_sz; void* img_SRAM_size; void* img_IMEM_size; void* dmem_size; void* version; void* signature; } ;
typedef  int /*<<< orphan*/  __le32 ;
typedef  int /*<<< orphan*/  __le16 ;

/* Variables and functions */
 void* le16_to_cpu (int /*<<< orphan*/ ) ; 
 void* le32_to_cpu (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void update_fwhdr(struct fw_hdr	*pfwhdr, const u8 *pmappedfw)
{
	pfwhdr->signature = le16_to_cpu(*(__le16 *)pmappedfw);
	pfwhdr->version = le16_to_cpu(*(__le16 *)(pmappedfw + 2));
	/* define the size of boot loader */
	pfwhdr->dmem_size = le32_to_cpu(*(__le32 *)(pmappedfw + 4));
	/* define the size of FW in IMEM */
	pfwhdr->img_IMEM_size = le32_to_cpu(*(__le32 *)(pmappedfw + 8));
	/* define the size of FW in SRAM */
	pfwhdr->img_SRAM_size = le32_to_cpu(*(__le32 *)(pmappedfw + 12));
	/* define the size of DMEM variable */
	pfwhdr->fw_priv_sz = le32_to_cpu(*(__le32 *)(pmappedfw + 16));
}