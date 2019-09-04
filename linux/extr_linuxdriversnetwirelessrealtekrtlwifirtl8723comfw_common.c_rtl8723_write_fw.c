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
typedef  int u32 ;
struct rtl_priv {int dummy; } ;
struct ieee80211_hw {int dummy; } ;
typedef  enum version_8723e { ____Placeholder_version_8723e } version_8723e ;

/* Variables and functions */
 int /*<<< orphan*/  COMP_FW ; 
 int /*<<< orphan*/  DBG_TRACE ; 
 int FW_8192C_PAGE_SIZE ; 
 int /*<<< orphan*/  RT_TRACE (struct rtl_priv*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  pr_err (char*,int) ; 
 int /*<<< orphan*/  rtl_fill_dummy (int*,int*) ; 
 int /*<<< orphan*/  rtl_fw_page_write (struct ieee80211_hw*,int,int*,int) ; 
 struct rtl_priv* rtl_priv (struct ieee80211_hw*) ; 

void rtl8723_write_fw(struct ieee80211_hw *hw,
		      enum version_8723e version,
		      u8 *buffer, u32 size, u8 max_page)
{
	struct rtl_priv *rtlpriv = rtl_priv(hw);
	u8 *bufferptr = buffer;
	u32 page_nums, remain_size;
	u32 page, offset;

	RT_TRACE(rtlpriv, COMP_FW, DBG_TRACE, "FW size is %d bytes,\n", size);

	rtl_fill_dummy(bufferptr, &size);

	page_nums = size / FW_8192C_PAGE_SIZE;
	remain_size = size % FW_8192C_PAGE_SIZE;

	if (page_nums > max_page) {
		pr_err("Page numbers should not greater than %d\n",
		       max_page);
	}
	for (page = 0; page < page_nums; page++) {
		offset = page * FW_8192C_PAGE_SIZE;
		rtl_fw_page_write(hw, page, (bufferptr + offset),
				  FW_8192C_PAGE_SIZE);
	}

	if (remain_size) {
		offset = page_nums * FW_8192C_PAGE_SIZE;
		page = page_nums;
		rtl_fw_page_write(hw, page, (bufferptr + offset), remain_size);
	}
	RT_TRACE(rtlpriv, COMP_FW, DBG_TRACE, "FW write done.\n");
}