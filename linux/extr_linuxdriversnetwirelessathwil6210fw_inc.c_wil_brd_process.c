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
typedef  size_t u16 ;
struct wil_fw_record_head {int /*<<< orphan*/  type; int /*<<< orphan*/  size; } ;
struct wil_fw_record_data {int dummy; } ;
struct wil6210_priv {size_t brd_file_max_size; int /*<<< orphan*/  brd_file_addr; } ;

/* Variables and functions */
 int EINVAL ; 
 int __fw_handle_data (struct wil6210_priv*,struct wil_fw_record_head const*,size_t,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cpu_to_le32 (int /*<<< orphan*/ ) ; 
 size_t le16_to_cpu (int /*<<< orphan*/ ) ; 
 int le32_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wil_dbg_fw (struct wil6210_priv*,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wil_err_fw (struct wil6210_priv*,char*,size_t) ; 
 size_t wil_fw_type_data ; 

__attribute__((used)) static int wil_brd_process(struct wil6210_priv *wil, const void *data,
			   size_t size)
{
	int rc = 0;
	const struct wil_fw_record_head *hdr = data;
	size_t s, hdr_sz;
	u16 type;

	/* Assuming the board file includes only one header record and one data
	 * record. Each record starts with wil_fw_record_head.
	 */
	if (size < sizeof(*hdr))
		return -EINVAL;
	s = sizeof(*hdr) + le32_to_cpu(hdr->size);
	if (s > size)
		return -EINVAL;

	/* Skip the header record and handle the data record */
	hdr = (const void *)hdr + s;
	size -= s;
	if (size < sizeof(*hdr))
		return -EINVAL;
	hdr_sz = le32_to_cpu(hdr->size);

	if (wil->brd_file_max_size && hdr_sz > wil->brd_file_max_size)
		return -EINVAL;
	if (sizeof(*hdr) + hdr_sz > size)
		return -EINVAL;
	if (hdr_sz % 4) {
		wil_err_fw(wil, "unaligned record size: %zu\n",
			   hdr_sz);
		return -EINVAL;
	}
	type = le16_to_cpu(hdr->type);
	if (type != wil_fw_type_data) {
		wil_err_fw(wil, "invalid record type for board file: %d\n",
			   type);
		return -EINVAL;
	}
	if (hdr_sz < sizeof(struct wil_fw_record_data)) {
		wil_err_fw(wil, "data record too short: %zu\n", hdr_sz);
		return -EINVAL;
	}

	wil_dbg_fw(wil, "using addr from fw file: [0x%08x]\n",
		   wil->brd_file_addr);

	rc = __fw_handle_data(wil, &hdr[1], hdr_sz,
			      cpu_to_le32(wil->brd_file_addr));

	return rc;
}